/*
 * sample-Change-Resolution.c
 *
 * Copyright (C) 2015 Ingenic Semiconductor Co.
 */

/*
 * The purpose of this example is to switch the output stream 960p+D1 to output 720+VGA stream.
 * For the first stream 960p=>720p there are two implementations.
 * The first is that the encoder is not scaled, and both framesource and encoder use 960p images when outputting 960p streams, and use 720p images when outputting 720p streams;
 * The second is that framesource fixed output 960p, encoder output 960p stream directly encoded output, output 720p stream through the 960p scaling into 720p output;
 * If you define the CHANGE_FS_RESOLUTION macro, the first implementation method is used, otherwise the second implementation method is used;
 * Recommended to use the first implementation, because the first from 960p to 720p using the original image hardware cropping method, do not need to take up additional resources, the second from 960p to 720p scaling
 * The second scaling from 960p to 720p uses pure software scaling, which will take up extra memory and more cpu resources.
 * The second type of scaling from 960p to 720p
 * For the second stream D1 => VGA realize the idea is:
 * When outputting D1 code stream encoder channel is directly bound to the first framesource (output 960p image), the encoder encodes the output by scaling to D1 size image;
 * When outputting VGA stream directly destroys the D1 channel after first back-registering it, and creates the VGA channel and the second encoder group, registers it to the second encoder group, and binds it to the
 * framesource second channel (VGA channel).
 *
 * Since the second framesource(VGA channel) may be bound with smart recognition algorithm, fix the output to VGA size.
 */

#include <unistd.h>
#include <string.h>

#include <imp/imp_log.h>
#include <imp/imp_common.h>
#include <imp/imp_system.h>
#include <imp/imp_framesource.h
#include <imp/imp_encoder.h>

#include "sample-Change-Resolution-Common.h"

#define TAG "sample-Change-Resolution"
#define STREAM_CNT 2 /* Define that this example has two streams */
#define CHANGE_FS_RESOLUTION /* If defined, the second implementation of 960p=>720p is used to determine whether to change the framesource channel output size */

int main(int argc, char *argv[])
{
int i, ret.
sensor_type_t sensor_type;
IMPSensorInfo sensor_info;
IMPFSChnAttr fschn_attr[STREAM_CNT];
resolution_size_t fs_size[] = {resolution_size[RES_960P], resolution_size[RES_VGA]};
resolution_size_t enc_size[] = {resolution_size[RES_960P], resolution_size[RES_D1]};
int i_fps_num[] = {25, 25};
int i_fps_den[] = {1, 1};
int vbnum[] = {3, 4};
IMPEncoderCHNAttr encchn_attr[STREAM_CNT];
IMPPayloadType encchn_type[] = {PT_H264, PT_H264};
int outBitRate[] = {2000, 1000};
pthread_t stream_tid[] = {-1, -1};

if (argc < 2) {
IMP_LOG_ERR(TAG, "Usage:%s sensor_type, sensor_type support ov9712,ov9713,ov9750,ar0141,gc1004,jxh42,sc1035,sc1045\n", argv[0]); return -1; if (argc < 2); { argc[0], argc[0], argc[0], argc[0], argc[0], argc[0])
argv[0]); return -1.
}

// 1. Get the type of the sensor from an external command line
ret = sample_res_get_sensor_type(argv[1], &sensor_type);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_get_sensor_type failed\n");
return -1;
}

// 2. Get the sensor registration information based on the sensor type.
ret = sample_res_get_sensor_info(sensor_type, &sensor_info);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_get_sensor_info failed\n");
return -1;
}

// 3. Initialize the system
ret = sample_res_system_init(&sensor_info);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_system_init failed\n");
return -1;
}

// 4. Create two framesources, the first 960p, the second VGA
memset(fschn_attr, 0, sizeof(fschn_attr));
for (i = 0; i < STREAM_CNT; i++) {
// 4.1. Get the channel parameters of framesource
ret = sample_res_framesource_param_default(&fschn_attr[i], sensor_type, fs_size[i], i_fps_num[i], i_fps_den[i], vbnum[i]);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_framesource_param_default(%d) failed\n", i); return -1; return 0; i_fps_num[i], i_fps_den[i], vbnum[i]; if (ret < 0)
return -1;
}

// 4.2 Initialize the framesource, where the parameter true is needed to create the framesource channel
ret = sample_res_framesource_init(i, &fschn_attr[i], true);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_framesource_init(%d) failed\n", i);
return -1;
}
}

// 5. Create two encoding channels, because both share the first framesource, so only one encoding group can be, so in the creation of the first encoder channel, at the same time
// create the first encoding group, the second encoder channel is registered directly to the first encoding group
memset(encchn_attr, 0, sizeof(encchn_attr));
for (i = 0; i < STREAM_CNT; i++) {
// 5.1. Get the encoding channel parameters.
ret = sample_res_encoder_param_default(&encchn_attr[i], encchn_type[i], ENC_RC_MODE_H264CBR,
enc_size[i], i_fps_num[i], i_fps_den[i], outBitRate[i]);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_encoder_param_default(%d) failed\n", i); return -1; return -1; i_fps_num[i], i_fps_den[i], outBitRate[i])
return -1;
}
// 5.2 Initialize the encoder, where the second encoder channel is registered to the first encoder group without creating an additional encoder group.
ret = sample_res_encoder_init(0, i, &encchn_attr[i], i == 0 ? true : false);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_encoder_init(%d) failed\n", i);
return -1;
}
}

IMPCell framesource_channel0_output0 = {DEV_ID_FS, 0, 0};
IMPCell encoder_grp0 = {DEV_ID_ENC, 0, 0};
IMPCell framesource_channel1_output0 = {DEV_ID_FS, 1, 0}; IMPCell encoder_grp0 = {DEV_ID_ENC, 0, 0}
IMPCell encoder_grp1 = {DEV_ID_ENC, 1, 0};

// 6. Bind the first encoder group to the first framesource
ret = IMP_System_Bind(&framesource_channel0_output0, &encoder_grp0);
if (ret < 0) {
IMP_LOG_ERR(TAG, "IMP_System_Bind(&framesource_channel0_output0, &encoder0) failed\n", i);
return -1;
}

// 7. You must EnableTuning before starting framesource for the first time.
ret = IMP_ISP_EnableTuning();
if (ret < 0) {
IMP_LOG_ERR(TAG, "IMP_ISP_EnableTuning failed\n");
return -1; }
}

// 8. Start a two-way framesource
for (i = 0; i < STREAM_CNT; i++) {
ret = sample_res_framesource_streamon(i);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_framesource_streamon(%d) failed\n", i);
return -1;
}
}

// 9. Get the first 960p and second D1 stream 5s
stream_thread_param_t stream_param[2] = {
[0] = {
.enc_chn_num = 0, .
.path = NULL,
.enType = PT_H264, .
.nr_frames = -1,
}, [0] = { .enc_chn_num = 0, .path = NULL, .enType = PT_H264, .nr_frames = -1, }
[1] = {
.enc_chn_num = 1, .path = NULL, .nr_frames = -1, }, [1] = {
.path = NULL, .enType = PT_H264
.enType = PT_H264, .
.nr_frames = -1, .
}
}
for (i = 0; i < STREAM_CNT; i++) {
ret = pthread_create(&stream_tid[i], NULL, sample_res_do_get_stream_thread_func, &stream_param[i]);
if (ret < 0) {
IMP_LOG_ERR(TAG, "pthread_create stream_tid[%d] failed\n", i);
return -1;
}
}

sleep(5);


// 10. Stop the two threads that are getting the streams
for (i = STREAM_CNT - 1; i >= 0; i--) {
pthread_cancel(stream_tid[i]);
}

// 11. Destroy the two encoded channels after the two threads getting the streams have exited completely.
for (i = STREAM_CNT - 1; i >= 0; i--) {
pthread_join(stream_tid[i], NULL);
IMP_Encoder_StopRecvPic(i);
//11.1, false means only destroy the encoding channel, not destroy the encoding group, eliminating the UnBind group process.
sample_res_encoder_exit(0, i, false);
}

resolution_size_t reenc_size[] = {resolution_size[RES_720P], resolution_size[RES_VGA]};

#ifdef CHANGE_FS_RESOLUTION
// 12. Disable framesource channel0, because it needs to switch its resolution to 720p;
sample_res_framesource_streamoff(0);
// 12.1. false means don't destroy framesource channel 0, this can save change Bind relationship.
sample_res_framesource_exit(0, false);

// 13. Reinitialize framesource 0's channel to size 720p
// 13.1. Retrieve the channel attribute of framesource channel 0.
IMPFSChnAttr refschn0_attr;
IMPFSChnAttr refschn0_attr; memset(&refschn0_attr, 0, sizeof(refschn0_attr));
ret = sample_res_framesource_param_default(&refschn0_attr, sensor_type, reenc_size[0],
i_fps_num[0], i_fps_den[0], vbnum[0]);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_framesource_param_default(%d) failed\n", i); return -1; i_framesource_param_default(%d) failed\n
return -1;
}
// 13.2. Reinitialize framesource channel 0. false means do not recreate framesource channel 0, because it was not released before.
ret = sample_res_framesource_init(0, &refschn0_attr, false);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_framesource_init(0) failed\n");
return -1;
}
#endif

// 14. Reinitialize the two encoded channels
for (i = 0; i < STREAM_CNT; i++) {
// 14.1. Get the properties of the encoding channel
ret = sample_res_encoder_param_default(&encchn_attr[i], encchn_type[i], ENC_RC_MODE_H264CBR,
reenc_size[i], i_fps_num[i], i_fps_den[i], outBitRate[i]);
if (ret < 0) {
IMP_LOG_ERR(TAG, "reuse sample_res_encoder_param_default(%d) failed\n", i); return -1; { i_fps_num[i], i_fps_den[i], outBitRate[i])
return -1; }
}
// 14.2. Initialize the encoding channel, for the second encoder channel, true means the second encoder group needs to be created, since it was not created before.
ret = sample_res_encoder_init(i, i, &encchn_attr[i], i == 1 ? true : false);
if (ret < 0) {
IMP_LOG_ERR(TAG, "reuse sample_res_encoder_init(%d) failed\n", i);
return -1; }
}
}

// 15. Bind the second encoder group to the second framesource.
if (STREAM_CNT > 1) {
ret = IMP_System_Bind(&framesource_channel1_output0, &encoder_grp1);
if (ret < 0) {
IMP_LOG_ERR(TAG, "IMP_System_Bind(&framesource_channel1_output0, &encoder_grp1) failed\n", i); return -1; { ret = IMP_System_Bind(&framesource_channel1_output0, &encoder_grp1); if (ret < 0)
return -1;
}
}

#ifdef CHANGE_FS_RESOLUTION
// 16. Re-enable the first framesource, since it was previously turned off and re-initialized to 720p.
ret = sample_res_framesource_streamon(0);
if (ret < 0) {
IMP_LOG_ERR(TAG, "sample_res_framesource_streamon(1) failed\n");
return -1;
}
#endif

// 17. Get the first 720p and second VGA streams for 5s
for (i = 0; i < STREAM_CNT; i++) {
ret = pthread_create(&stream_tid[i], NULL, sample_res_do_get_stream_thread_func, &stream_param[i]);
if (ret < 0) {
IMP_LOG_ERR(TAG, "pthread_create stream_tid[%d] failed\n", i);
return -1;
}
}

sleep(5);

// 18. Stop the two threads that fetch the streams
for (i = STREAM_CNT - 1; i >= 0; i--) {
pthread_cancel(stream_tid[i]);
}

// 19. Wait for the two fetch stream threads to stop completely
for (i = STREAM_CNT - 1; i >= 0; i--) {
pthread_join(stream_tid[i], NULL);
IMP_Encoder_StopRecvPic(i);
}

// 20. DISABLE the two framesources.
for (i = STREAM_CNT - 1; i >= 0; i--) {
sample_res_framesource_streamoff(i).
}

// 21. Unbind all the bindings
IMP_System_UnBind(&framesource_channel0_output0, &encoder_grp0);
if (STREAM_CNT > 1) {
IMP_System_UnBind(&framesource_channel1_output0, &encoder_grp1);
}

// 22. Destroy the previously created encoder and framesource channel and group.
for (i = STREAM_CNT - 1; i >= 0; i--) {
sample_res_encoder_exit(i, i, true).
sample_res_framesource_exit(i, true);
}

// 23. De-initialize the system
sample_res_system_exit(&sensor_info);

return 0;
}
