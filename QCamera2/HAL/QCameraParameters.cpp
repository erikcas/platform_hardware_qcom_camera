/* Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#define LOG_TAG "QCameraParameters"

#include <utils/Log.h>
#include <utils/Errors.h>
#include <string.h>
#include <stdlib.h>
#include <gralloc_priv.h>
#include "QCameraParameters.h"

namespace qcamera {
// Parameter keys to communicate between camera application and driver.
const char QCameraParameters::KEY_QC_SUPPORTED_HFR_SIZES[] = "hfr-size-values";
const char QCameraParameters::KEY_QC_PREVIEW_FRAME_RATE_MODE[] = "preview-frame-rate-mode";
const char QCameraParameters::KEY_QC_SUPPORTED_PREVIEW_FRAME_RATE_MODES[] = "preview-frame-rate-modes";
const char QCameraParameters::KEY_QC_PREVIEW_FRAME_RATE_AUTO_MODE[] = "frame-rate-auto";
const char QCameraParameters::KEY_QC_PREVIEW_FRAME_RATE_FIXED_MODE[] = "frame-rate-fixed";
const char QCameraParameters::KEY_QC_TOUCH_AF_AEC[] = "touch-af-aec";
const char QCameraParameters::KEY_QC_SUPPORTED_TOUCH_AF_AEC[] = "touch-af-aec-values";
const char QCameraParameters::KEY_QC_TOUCH_INDEX_AEC[] = "touch-index-aec";
const char QCameraParameters::KEY_QC_TOUCH_INDEX_AF[] = "touch-index-af";
const char QCameraParameters::KEY_QC_SCENE_DETECT[] = "scene-detect";
const char QCameraParameters::KEY_QC_SUPPORTED_SCENE_DETECT[] = "scene-detect-values";
const char QCameraParameters::KEY_QC_ISO_MODE[] = "iso";
const char QCameraParameters::KEY_QC_SUPPORTED_ISO_MODES[] = "iso-values";
const char QCameraParameters::KEY_QC_LENSSHADE[] = "lensshade";
const char QCameraParameters::KEY_QC_SUPPORTED_LENSSHADE_MODES[] = "lensshade-values";
const char QCameraParameters::KEY_QC_AUTO_EXPOSURE[] = "auto-exposure";
const char QCameraParameters::KEY_QC_SUPPORTED_AUTO_EXPOSURE[] = "auto-exposure-values";
const char QCameraParameters::KEY_QC_DENOISE[] = "denoise";
const char QCameraParameters::KEY_QC_SUPPORTED_DENOISE[] = "denoise-values";
const char QCameraParameters::KEY_QC_FOCUS_ALGO[] = "selectable-zone-af";
const char QCameraParameters::KEY_QC_SUPPORTED_FOCUS_ALGOS[] = "selectable-zone-af-values";
const char QCameraParameters::KEY_QC_FACE_DETECTION[] = "face-detection";
const char QCameraParameters::KEY_QC_SUPPORTED_FACE_DETECTION[] = "face-detection-values";
const char QCameraParameters::KEY_QC_MEMORY_COLOR_ENHANCEMENT[] = "mce";
const char QCameraParameters::KEY_QC_SUPPORTED_MEM_COLOR_ENHANCE_MODES[] = "mce-values";
const char QCameraParameters::KEY_QC_VIDEO_HIGH_FRAME_RATE[] = "video-hfr";
const char QCameraParameters::KEY_QC_SUPPORTED_VIDEO_HIGH_FRAME_RATE_MODES[] = "video-hfr-values";
const char QCameraParameters::KEY_QC_REDEYE_REDUCTION[] = "redeye-reduction";
const char QCameraParameters::KEY_QC_SUPPORTED_REDEYE_REDUCTION[] = "redeye-reduction-values";
const char QCameraParameters::KEY_QC_HIGH_DYNAMIC_RANGE_IMAGING[] = "hdr";
const char QCameraParameters::KEY_QC_SUPPORTED_HDR_IMAGING_MODES[] = "hdr-values";
const char QCameraParameters::KEY_QC_ZSL[] = "zsl";
const char QCameraParameters::KEY_QC_SUPPORTED_ZSL_MODES[] = "zsl-values";
const char QCameraParameters::KEY_QC_ZSL_BURST_INTERVAL[] = "capture-burst-interval";
const char QCameraParameters::KEY_QC_ZSL_BURST_LOOKBACK[] = "capture-burst-retroactive";
const char QCameraParameters::KEY_QC_ZSL_QUEUE_DEPTH[] = "capture-burst-queue-depth";
const char QCameraParameters::KEY_QC_CAMERA_MODE[] = "camera-mode";
const char QCameraParameters::KEY_QC_AE_BRACKET_HDR[] = "ae-bracket-hdr";
const char QCameraParameters::KEY_QC_SUPPORTED_AE_BRACKET_HDR_MODES[] = "ae-bracket-hdr-values";
const char QCameraParameters::KEY_QC_SUPPORTED_RAW_FORMATS[] = "raw-format-values";
const char QCameraParameters::KEY_QC_RAW_FORMAT[] = "raw-format";
const char QCameraParameters::KEY_QC_ORIENTATION[] = "orientation";
const char QCameraParameters::KEY_QC_SELECTABLE_ZONE_AF[] = "selectable-zone-af";
const char QCameraParameters::KEY_QC_CAPTURE_BURST_EXPOSURE[] = "capture-burst-exposures";
const char QCameraParameters::KEY_QC_NUM_SNAPSHOT_PER_SHUTTER[] = "num-snaps-per-shutter";
const char QCameraParameters::KEY_QC_NO_DISPLAY_MODE[] = "no-display-mode";
const char QCameraParameters::KEY_QC_RAW_PICUTRE_SIZE[] = "raw-size";
// Values for effect settings.
const char QCameraParameters::EFFECT_EMBOSS[] = "emboss";
const char QCameraParameters::EFFECT_SKETCH[] = "sketch";
const char QCameraParameters::EFFECT_NEON[] = "neon";

// Values for auto exposure settings.
const char QCameraParameters::TOUCH_AF_AEC_OFF[] = "touch-off";
const char QCameraParameters::TOUCH_AF_AEC_ON[] = "touch-on";

// Values for scene mode settings.
const char QCameraParameters::SCENE_MODE_ASD[] = "asd";   // corresponds to CAMERA_BESTSHOT_AUTO in HAL
const char QCameraParameters::SCENE_MODE_BACKLIGHT[] = "backlight";
const char QCameraParameters::SCENE_MODE_FLOWERS[] = "flowers";
const char QCameraParameters::SCENE_MODE_AR[] = "AR";

// Formats for setPreviewFormat and setPictureFormat.
const char QCameraParameters::PIXEL_FORMAT_YUV420SP_ADRENO[] = "yuv420sp-adreno";
const char QCameraParameters::PIXEL_FORMAT_YV12[] = "yuv420p";
const char QCameraParameters::PIXEL_FORMAT_NV12[] = "nv12";

// Values for raw image formats
const char QCameraParameters::QC_PIXEL_FORMAT_YUV_RAW_8BIT[] = "yuv-raw8";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8GBRG[] = "bayer-qcom-8gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8GRBG[] = "bayer-qcom-8grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8RGGB[] = "bayer-qcom-8rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8BGGR[] = "bayer-qcom-8bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10GBRG[] = "bayer-qcom-10gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10GRBG[] = "bayer-qcom-10grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10RGGB[] = "bayer-qcom-10rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10BGGR[] = "bayer-qcom-10bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12GBRG[] = "bayer-qcom-12gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12GRBG[] = "bayer-qcom-12grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12RGGB[] = "bayer-qcom-12rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12BGGR[] = "bayer-qcom-12bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8GBRG[] = "bayer-mipi-8gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8GRBG[] = "bayer-mipi-8grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8RGGB[] = "bayer-mipi-8rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8BGGR[] = "bayer-mipi-8bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10GBRG[] = "bayer-mipi-10gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10GRBG[] = "bayer-mipi-10grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10RGGB[] = "bayer-mipi-10rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10BGGR[] = "bayer-mipi-10bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12GBRG[] = "bayer-mipi-12gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12GRBG[] = "bayer-mipi-12grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12RGGB[] = "bayer-mipi-12rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12BGGR[] = "bayer-mipi-12bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8GBRG[] = "bayer-ideal-qcom-8gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8GRBG[] = "bayer-ideal-qcom-8grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8RGGB[] = "bayer-ideal-qcom-8rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8BGGR[] = "bayer-ideal-qcom-8bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10GBRG[] = "bayer-ideal-qcom-10gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10GRBG[] = "bayer-ideal-qcom-10grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10RGGB[] = "bayer-ideal-qcom-10rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10BGGR[] = "bayer-ideal-qcom-10bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12GBRG[] = "bayer-ideal-qcom-12gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12GRBG[] = "bayer-ideal-qcom-12grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12RGGB[] = "bayer-ideal-qcom-12rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12BGGR[] = "bayer-ideal-qcom-12bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8GBRG[] = "bayer-ideal-mipi-8gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8GRBG[] = "bayer-ideal-mipi-8grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8RGGB[] = "bayer-ideal-mipi-8rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8BGGR[] = "bayer-ideal-mipi-8bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10GBRG[] = "bayer-ideal-mipi-10gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10GRBG[] = "bayer-ideal-mipi-10grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10RGGB[] = "bayer-ideal-mipi-10rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10BGGR[] = "bayer-ideal-mipi-10bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12GBRG[] = "bayer-ideal-mipi-12gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12GRBG[] = "bayer-ideal-mipi-12grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12RGGB[] = "bayer-ideal-mipi-12rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12BGGR[] = "bayer-ideal-mipi-12bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8GBRG[] = "bayer-ideal-plain8-8gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8GRBG[] = "bayer-ideal-plain8-8grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8RGGB[] = "bayer-ideal-plain8-8rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8BGGR[] = "bayer-ideal-plain8-8bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8GBRG[] = "bayer-ideal-plain16-8gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8GRBG[] = "bayer-ideal-plain16-8grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8RGGB[] = "bayer-ideal-plain16-8rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8BGGR[] = "bayer-ideal-plain16-8bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10GBRG[] = "bayer-ideal-plain16-10gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10GRBG[] = "bayer-ideal-plain16-10grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10RGGB[] = "bayer-ideal-plain16-10rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10BGGR[] = "bayer-ideal-plain16-10bggr";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12GBRG[] = "bayer-ideal-plain16-12gbrg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12GRBG[] = "bayer-ideal-plain16-12grbg";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12RGGB[] = "bayer-ideal-plain16-12rggb";
const char QCameraParameters::QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12BGGR[] = "bayer-ideal-plain16-12bggr";

// Values for ISO Settings
const char QCameraParameters::ISO_AUTO[] = "auto";
const char QCameraParameters::ISO_HJR[] = "ISO_HJR";
const char QCameraParameters::ISO_100[] = "ISO100";
const char QCameraParameters::ISO_200[] = "ISO200";
const char QCameraParameters::ISO_400[] = "ISO400";
const char QCameraParameters::ISO_800[] = "ISO800";
const char QCameraParameters::ISO_1600[] = "ISO1600";

// Values for auto exposure settings.
const char QCameraParameters::AUTO_EXPOSURE_FRAME_AVG[] = "frame-average";
const char QCameraParameters::AUTO_EXPOSURE_CENTER_WEIGHTED[] = "center-weighted";
const char QCameraParameters::AUTO_EXPOSURE_SPOT_METERING[] = "spot-metering";
const char QCameraParameters::AUTO_EXPOSURE_SMART_METERING[] = "smart-metering";
const char QCameraParameters::AUTO_EXPOSURE_USER_METERING[] = "user-metering";
const char QCameraParameters::AUTO_EXPOSURE_SPOT_METERING_ADV[] = "spot-metering-adv";
const char QCameraParameters::AUTO_EXPOSURE_CENTER_WEIGHTED_ADV[] = "center-weighted-adv";

const char QCameraParameters::KEY_QC_GPS_LATITUDE_REF[] = "gps-latitude-ref";
const char QCameraParameters::KEY_QC_GPS_LONGITUDE_REF[] = "gps-longitude-ref";
const char QCameraParameters::KEY_QC_GPS_ALTITUDE_REF[] = "gps-altitude-ref";
const char QCameraParameters::KEY_QC_GPS_STATUS[] = "gps-status";

const char QCameraParameters::KEY_QC_HISTOGRAM[] = "histogram";
const char QCameraParameters::KEY_QC_SUPPORTED_HISTOGRAM_MODES[] = "histogram-values";

const char QCameraParameters::VALUE_ENABLE[] = "enable";
const char QCameraParameters::VALUE_DISABLE[] = "disable";
const char QCameraParameters::VALUE_OFF[] = "off";
const char QCameraParameters::VALUE_ON[] = "on";
const char QCameraParameters::VALUE_TRUE[] = "true";
const char QCameraParameters::VALUE_FALSE[] = "false";

const char QCameraParameters::KEY_QC_SHARPNESS[] = "sharpness";
const char QCameraParameters::KEY_QC_MIN_SHARPNESS[] = "min-sharpness";
const char QCameraParameters::KEY_QC_MAX_SHARPNESS[] = "max-sharpness";
const char QCameraParameters::KEY_QC_SHARPNESS_STEP[] = "sharpness-step";
const char QCameraParameters::KEY_QC_CONTRAST[] = "contrast";
const char QCameraParameters::KEY_QC_MIN_CONTRAST[] = "min-contrast";
const char QCameraParameters::KEY_QC_MAX_CONTRAST[] = "max-contrast";
const char QCameraParameters::KEY_QC_CONTRAST_STEP[] = "contrast-step";
const char QCameraParameters::KEY_QC_SATURATION[] = "saturation";
const char QCameraParameters::KEY_QC_MIN_SATURATION[] = "min-saturation";
const char QCameraParameters::KEY_QC_MAX_SATURATION[] = "max-saturation";
const char QCameraParameters::KEY_QC_SATURATION_STEP[] = "saturation-step";
const char QCameraParameters::KEY_QC_BRIGHTNESS[] = "luma-adaptation";
const char QCameraParameters::KEY_QC_MIN_BRIGHTNESS[] = "min-brightness";
const char QCameraParameters::KEY_QC_MAX_BRIGHTNESS[] = "max-brightness";
const char QCameraParameters::KEY_QC_BRIGHTNESS_STEP[] = "brightness-step";
const char QCameraParameters::KEY_QC_SCE_FACTOR[] = "skinToneEnhancement";
const char QCameraParameters::KEY_QC_MIN_SCE_FACTOR[] = "min-sce-factor";
const char QCameraParameters::KEY_QC_MAX_SCE_FACTOR[] = "max-sce-factor";
const char QCameraParameters::KEY_QC_SCE_FACTOR_STEP[] = "sce-factor-step";

const char QCameraParameters::KEY_QC_SUPPORTED_CAMERA_FEATURES[] = "qc-camera-features";
const char QCameraParameters::KEY_QC_MAX_NUM_REQUESTED_FACES[] = "qc-max-num-requested-faces";

//Values for DENOISE
const char QCameraParameters::DENOISE_OFF[] = "denoise-off";
const char QCameraParameters::DENOISE_ON[] = "denoise-on";

// Values for selectable zone af Settings
const char QCameraParameters::FOCUS_ALGO_AUTO[] = "auto";
const char QCameraParameters::FOCUS_ALGO_SPOT_METERING[] = "spot-metering";
const char QCameraParameters::FOCUS_ALGO_CENTER_WEIGHTED[] = "center-weighted";
const char QCameraParameters::FOCUS_ALGO_FRAME_AVERAGE[] = "frame-average";

// Values for HFR settings.
const char QCameraParameters::VIDEO_HFR_OFF[] = "off";
const char QCameraParameters::VIDEO_HFR_2X[] = "60";
const char QCameraParameters::VIDEO_HFR_3X[] = "90";
const char QCameraParameters::VIDEO_HFR_4X[] = "120";
const char QCameraParameters::VIDEO_HFR_5X[] = "150";

// Values for HDR Bracketing settings.
const char QCameraParameters::AE_BRACKET_HDR_OFF[] = "Off";
const char QCameraParameters::AE_BRACKET_HDR[] = "HDR";
const char QCameraParameters::AE_BRACKET[] = "AE-Bracket";

static const char* portrait = "portrait";
static const char* landscape = "landscape";

const cam_dimension_t QCameraParameters::THUMBNAIL_SIZES_MAP[] = {
    { 512, 288 }, //1.777778
    { 480, 288 }, //1.666667
    { 256, 154 }, //1.66233
    { 432, 288 }, //1.5
    { 320, 240 }, //1.33333
    { 176, 144 }, //1.222222
};

const QCameraParameters::QCameraMap QCameraParameters::AUTO_EXPOSURE_MAP[] = {
    { AUTO_EXPOSURE_FRAME_AVG,           CAM_AEC_MODE_FRAME_AVERAGE },
    { AUTO_EXPOSURE_CENTER_WEIGHTED,     CAM_AEC_MODE_CENTER_WEIGHTED },
    { AUTO_EXPOSURE_SPOT_METERING,       CAM_AEC_MODE_SPOT_METERING },
    { AUTO_EXPOSURE_SMART_METERING,      CAM_AEC_MODE_SMART_METERING },
    { AUTO_EXPOSURE_USER_METERING,       CAM_AEC_MODE_USER_METERING },
    { AUTO_EXPOSURE_SPOT_METERING_ADV,   CAM_AEC_MODE_SPOT_METERING_ADV },
    { AUTO_EXPOSURE_CENTER_WEIGHTED_ADV, CAM_AEC_MODE_CENTER_WEIGHTED_ADV },
};

const QCameraParameters::QCameraMap QCameraParameters::PREVIEW_FORMATS_MAP[] = {
    {PIXEL_FORMAT_YUV420SP,        CAM_FORMAT_YUV_420_NV21},
    {PIXEL_FORMAT_YUV420P,         CAM_FORMAT_YUV_420_YV12},
    {PIXEL_FORMAT_YUV420SP_ADRENO, CAM_FORMAT_YUV_420_NV21_ADRENO},
    {PIXEL_FORMAT_YV12,            CAM_FORMAT_YUV_420_YV12},
    {PIXEL_FORMAT_NV12,            CAM_FORMAT_YUV_420_NV12}
};

const QCameraParameters::QCameraMap QCameraParameters::PICTURE_TYPES_MAP[] = {
    {PIXEL_FORMAT_JPEG,                          CAMERA_PICTURE_TYPE_JPEG},
    {QC_PIXEL_FORMAT_YUV_RAW_8BIT,               CAM_FORMAT_YUV_RAW_8BIT},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8GBRG,       CAM_FORMAT_BAYER_QCOM_RAW_8BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8GRBG,       CAM_FORMAT_BAYER_QCOM_RAW_8BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8RGGB,       CAM_FORMAT_BAYER_QCOM_RAW_8BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_8BGGR,       CAM_FORMAT_BAYER_QCOM_RAW_8BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10GBRG,      CAM_FORMAT_BAYER_QCOM_RAW_10BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10GRBG,      CAM_FORMAT_BAYER_QCOM_RAW_10BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10RGGB,      CAM_FORMAT_BAYER_QCOM_RAW_10BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_10BGGR,      CAM_FORMAT_BAYER_QCOM_RAW_10BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12GBRG,      CAM_FORMAT_BAYER_QCOM_RAW_12BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12GRBG,      CAM_FORMAT_BAYER_QCOM_RAW_12BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12RGGB,      CAM_FORMAT_BAYER_QCOM_RAW_12BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_QCOM_RAW_12BGGR,      CAM_FORMAT_BAYER_QCOM_RAW_12BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8GBRG,       CAM_FORMAT_BAYER_MIPI_RAW_8BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8GRBG,       CAM_FORMAT_BAYER_MIPI_RAW_8BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8RGGB,       CAM_FORMAT_BAYER_MIPI_RAW_8BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_8BGGR,       CAM_FORMAT_BAYER_MIPI_RAW_8BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10GBRG,      CAM_FORMAT_BAYER_MIPI_RAW_10BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10GRBG,      CAM_FORMAT_BAYER_MIPI_RAW_10BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10RGGB,      CAM_FORMAT_BAYER_MIPI_RAW_10BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_10BGGR,      CAM_FORMAT_BAYER_MIPI_RAW_10BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12GBRG,      CAM_FORMAT_BAYER_MIPI_RAW_12BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12GRBG,      CAM_FORMAT_BAYER_MIPI_RAW_12BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12RGGB,      CAM_FORMAT_BAYER_MIPI_RAW_12BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_MIPI_RAW_12BGGR,      CAM_FORMAT_BAYER_MIPI_RAW_12BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8GBRG,     CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_8BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8GRBG,     CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_8BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8RGGB,     CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_8BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_8BGGR,     CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_8BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10GBRG,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_10BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10GRBG,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_10BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10RGGB,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_10BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_10BGGR,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_10BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12GBRG,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_12BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12GRBG,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_12BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12RGGB,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_12BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_QCOM_12BGGR,    CAM_FORMAT_BAYER_IDEAL_RAW_QCOM_12BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8GBRG,     CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_8BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8GRBG,     CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_8BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8RGGB,     CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_8BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_8BGGR,     CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_8BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10GBRG,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_10BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10GRBG,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_10BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10RGGB,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_10BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_10BGGR,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_10BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12GBRG,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_12BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12GRBG,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_12BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12RGGB,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_12BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_MIPI_12BGGR,    CAM_FORMAT_BAYER_IDEAL_RAW_MIPI_12BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8GBRG,   CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN8_8BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8GRBG,   CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN8_8BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8RGGB,   CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN8_8BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN8_8BGGR,   CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN8_8BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8GBRG,  CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_8BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8GRBG,  CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_8BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8RGGB,  CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_8BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_8BGGR,  CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_8BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10GBRG, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_10BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10GRBG, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_10BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10RGGB, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_10BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_10BGGR, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_10BPP_BGGR},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12GBRG, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_12BPP_GBRG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12GRBG, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_12BPP_GRBG},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12RGGB, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_12BPP_RGGB},
    {QC_PIXEL_FORMAT_BAYER_IDEAL_PLAIN16_12BGGR, CAM_FORMAT_BAYER_IDEAL_RAW_PLAIN16_12BPP_BGGR}
};

const QCameraParameters::QCameraMap QCameraParameters::RAW_FORMATS_MAP[] = {
};

// TODO: enable all after metadata stream is enabled for auto_focus_done
const QCameraParameters::QCameraMap QCameraParameters::FOCUS_MODES_MAP[] = {
    //{ FOCUS_MODE_AUTO,               CAM_FOCUS_MODE_AUTO},
    { FOCUS_MODE_INFINITY,           CAM_FOCUS_MODE_INFINITY }
    //{ FOCUS_MODE_MACRO,              CAM_FOCUS_MODE_MACRO },
    //{ FOCUS_MODE_FIXED,              CAM_FOCUS_MODE_FIXED },
    //{ FOCUS_MODE_EDOF,               CAM_FOCUS_MODE_EDOF },
    //{ FOCUS_MODE_CONTINUOUS_PICTURE, CAM_FOCUS_MODE_CONTINOUS_PICTURE},
    //{ FOCUS_MODE_CONTINUOUS_VIDEO,   CAM_FOCUS_MODE_CONTINOUS_VIDEO }
};

const QCameraParameters::QCameraMap QCameraParameters::EFFECT_MODES_MAP[] = {
    { EFFECT_NONE,       CAM_EFFECT_MODE_OFF },
    { EFFECT_MONO,       CAM_EFFECT_MODE_MONO },
    { EFFECT_NEGATIVE,   CAM_EFFECT_MODE_NEGATIVE },
    { EFFECT_SOLARIZE,   CAM_EFFECT_MODE_SOLARIZE },
    { EFFECT_SEPIA,      CAM_EFFECT_MODE_SEPIA },
    { EFFECT_POSTERIZE,  CAM_EFFECT_MODE_POSTERIZE },
    { EFFECT_WHITEBOARD, CAM_EFFECT_MODE_WHITEBOARD },
    { EFFECT_BLACKBOARD, CAM_EFFECT_MODE_BLACKBOARD },
    { EFFECT_AQUA,       CAM_EFFECT_MODE_AQUA },
    { EFFECT_EMBOSS,     CAM_EFFECT_MODE_EMBOSS },
    { EFFECT_SKETCH,     CAM_EFFECT_MODE_SKETCH },
    { EFFECT_NEON,       CAM_EFFECT_MODE_NEON }
};

const QCameraParameters::QCameraMap QCameraParameters::SCENE_MODES_MAP[] = {
    { SCENE_MODE_AUTO,           CAM_SCENE_MODE_OFF },
    { SCENE_MODE_ACTION,         CAM_SCENE_MODE_ACTION },
    { SCENE_MODE_PORTRAIT,       CAM_SCENE_MODE_PORTRAIT },
    { SCENE_MODE_LANDSCAPE,      CAM_SCENE_MODE_LANDSCAPE },
    { SCENE_MODE_NIGHT,          CAM_SCENE_MODE_NIGHT },
    { SCENE_MODE_NIGHT_PORTRAIT, CAM_SCENE_MODE_NIGHT_PORTRAIT },
    { SCENE_MODE_THEATRE,        CAM_SCENE_MODE_THEATRE },
    { SCENE_MODE_BEACH,          CAM_SCENE_MODE_BEACH },
    { SCENE_MODE_SNOW,           CAM_SCENE_MODE_SNOW },
    { SCENE_MODE_SUNSET,         CAM_SCENE_MODE_SUNSET },
    { SCENE_MODE_STEADYPHOTO,    CAM_SCENE_MODE_ANTISHAKE },
    { SCENE_MODE_FIREWORKS ,     CAM_SCENE_MODE_FIREWORKS },
    { SCENE_MODE_SPORTS ,        CAM_SCENE_MODE_SPORTS },
    { SCENE_MODE_PARTY,          CAM_SCENE_MODE_PARTY },
    { SCENE_MODE_CANDLELIGHT,    CAM_SCENE_MODE_CANDLELIGHT },
    { SCENE_MODE_ASD,            CAM_SCENE_MODE_AUTO },
    { SCENE_MODE_BACKLIGHT,      CAM_SCENE_MODE_BACKLIGHT },
    { SCENE_MODE_FLOWERS,        CAM_SCENE_MODE_FLOWERS },
    { SCENE_MODE_AR,             CAM_SCENE_MODE_AR },
};

const QCameraParameters::QCameraMap QCameraParameters::FLASH_MODES_MAP[] = {
    { FLASH_MODE_OFF,   CAM_FLASH_MODE_OFF },
    { FLASH_MODE_AUTO,  CAM_FLASH_MODE_AUTO },
    { FLASH_MODE_ON,    CAM_FLASH_MODE_ON },
    { FLASH_MODE_TORCH, CAM_FLASH_MODE_TORCH }
};

const QCameraParameters::QCameraMap QCameraParameters::FOCUS_ALGO_MAP[] = {
    { FOCUS_ALGO_AUTO,            CAM_FOCUS_ALGO_AUTO },
    { FOCUS_ALGO_SPOT_METERING,   CAM_FOCUS_ALGO_SPOT },
    { FOCUS_ALGO_CENTER_WEIGHTED, CAM_FOCUS_ALGO_CENTER_WEIGHTED },
    { FOCUS_ALGO_FRAME_AVERAGE,   CAM_FOCUS_ALGO_AVERAGE }
};

const QCameraParameters::QCameraMap QCameraParameters::WHITE_BALANCE_MODES_MAP[] = {
    { WHITE_BALANCE_AUTO,            CAM_WB_MODE_AUTO },
    { WHITE_BALANCE_INCANDESCENT,    CAM_WB_MODE_INCANDESCENT },
    { WHITE_BALANCE_FLUORESCENT,     CAM_WB_MODE_FLUORESCENT },
    { WHITE_BALANCE_WARM_FLUORESCENT,CAM_WB_MODE_WARM_FLUORESCENT},
    { WHITE_BALANCE_DAYLIGHT,        CAM_WB_MODE_DAYLIGHT },
    { WHITE_BALANCE_CLOUDY_DAYLIGHT, CAM_WB_MODE_CLOUDY_DAYLIGHT },
    { WHITE_BALANCE_TWILIGHT,        CAM_WB_MODE_TWILIGHT },
    { WHITE_BALANCE_SHADE,           CAM_WB_MODE_SHADE }
};

const QCameraParameters::QCameraMap QCameraParameters::ANTIBANDING_MODES_MAP[] = {
    { ANTIBANDING_OFF,  CAM_ANTIBANDING_MODE_OFF },
    { ANTIBANDING_50HZ, CAM_ANTIBANDING_MODE_50HZ },
    { ANTIBANDING_60HZ, CAM_ANTIBANDING_MODE_60HZ },
    { ANTIBANDING_AUTO, CAM_ANTIBANDING_MODE_AUTO }
};

const QCameraParameters::QCameraMap QCameraParameters::ISO_MODES_MAP[] = {
    { ISO_AUTO,  CAM_ISO_MODE_AUTO },
    { ISO_HJR,   CAM_ISO_MODE_DEBLUR },
    { ISO_100,   CAM_ISO_MODE_100 },
    { ISO_200,   CAM_ISO_MODE_200 },
    { ISO_400,   CAM_ISO_MODE_400 },
    { ISO_800,   CAM_ISO_MODE_800 },
    { ISO_1600,  CAM_ISO_MODE_1600 }
};

const QCameraParameters::QCameraMap QCameraParameters::HFR_MODES_MAP[] = {
    { VIDEO_HFR_OFF, CAM_HFR_MODE_OFF },
    { VIDEO_HFR_2X,  CAM_HFR_MODE_60FPS },
    { VIDEO_HFR_3X,  CAM_HFR_MODE_90FPS },
    { VIDEO_HFR_4X,  CAM_HFR_MODE_120FPS },
    { VIDEO_HFR_5X,  CAM_HFR_MODE_150FPS }
};

const QCameraParameters::QCameraMap QCameraParameters::HDR_BRACKETING_MODES_MAP[] = {
    { AE_BRACKET_HDR_OFF, CAM_HDR_BRACKETING_OFF },
    { AE_BRACKET_HDR,     CAM_HDR_MODE },
    { AE_BRACKET,         CAM_EXP_BRACKETING_MODE }
};

const QCameraParameters::QCameraMap QCameraParameters::ON_OFF_MODES_MAP[] = {
    { VALUE_OFF, 0 },
    { VALUE_ON,  1 }
};

const QCameraParameters::QCameraMap QCameraParameters::ENABLE_DISABLE_MODES_MAP[] = {
    { VALUE_ENABLE,  1 },
    { VALUE_DISABLE, 0 }
};

const QCameraParameters::QCameraMap QCameraParameters::DENOISE_ON_OFF_MODES_MAP[] = {
    { DENOISE_OFF, 0 },
    { DENOISE_ON,  1 }
};

const QCameraParameters::QCameraMap QCameraParameters::TRUE_FALSE_MODES_MAP[] = {
    { VALUE_FALSE, 0},
    { VALUE_TRUE,  1}
};

#define DEFAULT_CAMERA_AREA "(0, 0, 0, 0, 0)"
#define DATA_PTR(MEM_OBJ,INDEX) MEM_OBJ->getPtr( INDEX )

QCameraParameters::QCameraParameters()
    : CameraParameters(),
      m_pCapability(NULL),
      m_pCamOpsTbl(NULL),
      m_pParamHeap(NULL),
      m_pParamBuf(NULL),
      m_bZslMode(false),
      m_bRecordingHint(false),
      m_bHistogramEnabled(false),
      m_bFaceDetectionEnabled(false),
      m_bDebugFps(false),
      m_nDumpFrameEnabled(0),
      mFocusMode(CAM_FOCUS_MODE_MAX),
      mPreviewFormat(CAM_FORMAT_YUV_420_NV21),
      mPictureFormat(CAMERA_PICTURE_TYPE_JPEG),
      m_bNeedRestart(false),
      m_bNoDisplayMode(false),
      m_bWNROn(false),
      m_tempMap()
{
    char value[32];
    // TODO: may move to parameter instead of sysprop
    property_get("persist.debug.sf.showfps", value, "0");
    m_bDebugFps = atoi(value) > 0 ? true : false;
    property_get("persist.camera.dumpimg", value, "0");
    m_nDumpFrameEnabled = atoi(value);
}

QCameraParameters::QCameraParameters(const String8 &params)
    : CameraParameters(params),
    m_pCapability(NULL),
    m_pCamOpsTbl(NULL),
    m_pParamHeap(NULL),
    m_pParamBuf(NULL),
    m_bZslMode(false),
    m_bRecordingHint(false),
    m_bHistogramEnabled(false),
    m_bFaceDetectionEnabled(false),
    m_bDebugFps(false),
    m_nDumpFrameEnabled(0),
    mFocusMode(CAM_FOCUS_MODE_MAX),
    mPreviewFormat(CAM_FORMAT_YUV_420_NV21),
    mPictureFormat(CAMERA_PICTURE_TYPE_JPEG),
    m_bNeedRestart(false),
    m_bNoDisplayMode(false),
    m_bWNROn(false),
    m_tempMap()
{
}

QCameraParameters::~QCameraParameters()
{
    deinit();
}

String8 QCameraParameters::createSizesString(const cam_dimension_t *sizes, int len)
{
    String8 str;
    char buffer[32];

    if (len > 0) {
        snprintf(buffer, sizeof(buffer), "%dx%d", sizes[0].width, sizes[0].height);
        str.append(buffer);
    }
    for (int i = 1; i < len; i++) {
        snprintf(buffer, sizeof(buffer), ",%dx%d", sizes[i].width, sizes[i].height);
        str.append(buffer);
    }
    return str;
}

String8 QCameraParameters::createValuesString(const int *values,
                                              int len,
                                              const QCameraMap* map,
                                              int map_len)
{
    String8 str;
    int count = 0;

    for (int i = 0; i < len; i++ ) {
        for (int j = 0; j < map_len; j ++)
            if (map[j].val == values[i]) {
                if (NULL != map[j].desc) {
                    if (count > 0) {
                        str.append(",");
                    }
                    str.append(map[j].desc);
                    count++;
                    break; //loop j
                }
            }
    }
    return str;
}

String8 QCameraParameters::createValuesStringFromMap(const QCameraMap* map,
                                                     int map_len)
{
    String8 str;

    for (int i = 0; i < map_len; i++) {
        if (NULL != map[i].desc) {
            if (i > 0) {
                str.append(",");
            }
            str.append(map[i].desc);
        }
    }
    return str;
}

String8 QCameraParameters::createZoomRatioValuesString(int *zoomRatios, int length)
{
    String8 str;
    char buffer[32] = {0};

    if(length > 0){
        snprintf(buffer, sizeof(buffer), "%d", zoomRatios[0]);
        str.append(buffer);
    }

    for (int i =1;i<length;i++){
        memset(buffer, 0, sizeof(buffer));
        snprintf(buffer, sizeof(buffer), ",%d", zoomRatios[i]);
        str.append(buffer);
    }
    return str;
}

String8 QCameraParameters::createHfrValuesString(
                                const cam_hfr_info_t *values,
                                int len,
                                const QCameraMap* map,
                                int map_len)
{
    String8 str;
    int count = 0;

    for (int i = 0; i < len; i++ ) {
        for (int j = 0; j < map_len; j ++)
            if (map[j].val == (int)values[i].mode) {
                if (NULL != map[j].desc) {
                    if (count > 0) {
                        str.append(",");
                    }
                     str.append(map[j].desc);
                     count++;
                     break; //loop j
                }
            }
    }
    return str;
}

String8 QCameraParameters::createHfrSizesString(
                                const cam_hfr_info_t *values,
                                int len)
{
    String8 str;
    char buffer[32];

    if (len > 0) {
        snprintf(buffer, sizeof(buffer), "%dx%d",
                 values[0].dim.width, values[0].dim.height);
        str.append(buffer);
    }
    for (int i = 1; i < len; i++) {
        snprintf(buffer, sizeof(buffer), ",%dx%d",
                 values[i].dim.width, values[i].dim.height);
        str.append(buffer);
    }
    return str;
}

String8 QCameraParameters::createFpsString(const cam_fps_range_t *fps, int len)
{
    String8 str;
    char buffer[32];

    for (int i = 0; i < len; i++ ) {
        snprintf(buffer, sizeof(buffer), "%d", int(fps[i].max_fps * 1000));
        str.append(buffer);
        if (i < len-1)
            str.append(",");
    }
    return str;
}

String8 QCameraParameters::createFpsRangeString(const cam_fps_range_t* fps, int len)
{
    String8 str;
    char buffer[32];

    if (len > 0) {
        snprintf(buffer, sizeof(buffer), "(%d,%d)",
                 int(fps[0].min_fps * 1000),
                 int(fps[0].max_fps * 1000));
        str.append(buffer);
    }
    for (int i = 1; i < len; i++) {
        snprintf(buffer, sizeof(buffer), ",(%d,%d)",
                 int(fps[i].min_fps * 1000),
                 int(fps[i].max_fps * 1000));
        str.append(buffer);
    }
    return str;
}

int QCameraParameters::lookupAttr(const QCameraMap arr[], int len, const char *name)
{
    if (name) {
        for (int i = 0; i < len; i++) {
            if (!strcmp(arr[i].desc, name))
                return arr[i].val;
        }
    }
    return NAME_NOT_FOUND;
}

int32_t QCameraParameters::setPreviewSize(const QCameraParameters& params)
{
    int width, height;
    params.getPreviewSize(&width, &height);
    ALOGD("Requested preview size %d x %d", width, height);

    // Validate the preview size
    for (size_t i = 0; i < m_pCapability->preview_sizes_tbl_cnt; ++i) {
        if (width ==  m_pCapability->preview_sizes_tbl[i].width
           && height ==  m_pCapability->preview_sizes_tbl[i].height) {
            // check if need to restart preview in case of preview size change
            int old_width, old_height;
            CameraParameters::getPreviewSize(&old_width, &old_height);
            if (width != old_width || height != old_height) {
                m_bNeedRestart = true;
            }

            // set the new value
            char val[32];
            sprintf(val, "%dx%d", width, height);
            updateParamEntry(KEY_PREVIEW_SIZE, val);
            ALOGD("%s: %s", __func__, val);
            return NO_ERROR;
        }
    }
    ALOGE("Invalid preview size requested: %dx%d", width, height);
    return BAD_VALUE;
}

int32_t QCameraParameters::setPictureSize(const QCameraParameters& params)
{
    int width, height;
    params.getPictureSize(&width, &height);
    ALOGV("Requested picture size %d x %d", width, height);

    // Validate the picture size
    for (size_t i = 0; i < m_pCapability->picture_sizes_tbl_cnt; ++i) {
        if (width ==  m_pCapability->picture_sizes_tbl[i].width
           && height ==  m_pCapability->picture_sizes_tbl[i].height) {
            // check if need to restart preview in case of picture size change
            int old_width, old_height;
            CameraParameters::getPictureSize(&old_width, &old_height);
            if ((m_bZslMode || m_bRecordingHint) &&
                (width != old_width || height != old_height)) {
                m_bNeedRestart = true;
            }

            // set the new value
            char val[32];
            sprintf(val, "%dx%d", width, height);
            updateParamEntry(KEY_PICTURE_SIZE, val);
            ALOGD("%s: %s", __func__, val);
            return NO_ERROR;
        }
    }
    ALOGE("Invalid picture size requested: %dx%d", width, height);
    return BAD_VALUE;
}


int32_t QCameraParameters::setVideoSize(const QCameraParameters& params)
{
    const char *str= NULL;
    int width, height;
    ALOGV("%s: E", __func__);
    str = params.get(KEY_VIDEO_SIZE);
    if(!str) {
        //If application didn't set this parameter string, use the values from
        //getPreviewSize() as video dimensions.
        params.getPreviewSize(&width, &height);
        ALOGE("No Record Size requested, use the preview dimensions");
    } else {
        params.getVideoSize(&width, &height);
    }

    // Validate the video size
    for (size_t i = 0; i < m_pCapability->video_sizes_tbl_cnt; ++i) {
        if (width ==  m_pCapability->video_sizes_tbl[i].width
                && height ==  m_pCapability->video_sizes_tbl[i].height) {
            // check if need to restart preview in case of video size change
            int old_width, old_height;
            CameraParameters::getVideoSize(&old_width, &old_height);
            if (m_bRecordingHint &&
               (width != old_width || height != old_height)) {
                m_bNeedRestart = true;
            }

            // set the new value
            char val[32];
            sprintf(val, "%dx%d", width, height);
            updateParamEntry(KEY_VIDEO_SIZE, val);
            ALOGD("%s: %s", __func__, val);
            return NO_ERROR;
        }
    }

    ALOGE("Invalid video size requested: %dx%d", width, height);
    ALOGV("%s: X", __func__);
    return BAD_VALUE;
}

int32_t QCameraParameters::setPreviewFormat(const QCameraParameters& params)
{
    const char *str = params.getPreviewFormat();
    int32_t previewFormat =
        lookupAttr(PREVIEW_FORMATS_MAP,
                   sizeof(PREVIEW_FORMATS_MAP) / sizeof(QCameraMap),
                   str);
    if (previewFormat != NAME_NOT_FOUND) {
        mPreviewFormat = (cam_format_t)previewFormat;

        updateParamEntry(KEY_PREVIEW_FORMAT, str);
        ALOGE("%s: format %d\n", __func__, mPreviewFormat);
        return NO_ERROR;
    }
    ALOGE("Invalid preview format value: %s", (str == NULL) ? "NULL" : str);
    return BAD_VALUE;
}

int32_t QCameraParameters::setPictureFormat(const QCameraParameters& params)
{
    const char *str = params.getPictureFormat();
    int32_t pictureFormat =
        lookupAttr(PICTURE_TYPES_MAP,
                   sizeof(PICTURE_TYPES_MAP) / sizeof(QCameraMap),
                   str);
    if (pictureFormat != NAME_NOT_FOUND) {
        mPictureFormat = pictureFormat;

        updateParamEntry(KEY_PICTURE_FORMAT, str);
        ALOGE("%s: format %d\n", __func__, mPictureFormat);
        return NO_ERROR;
    }
    ALOGE("Invalid picture format value: %s", (str == NULL) ? "NULL" : str);
    return BAD_VALUE;
}

int32_t QCameraParameters::setJpegThumbnailSize(const QCameraParameters& params)
{
    int width = params.getInt(KEY_JPEG_THUMBNAIL_WIDTH);
    int height = params.getInt(KEY_JPEG_THUMBNAIL_HEIGHT);

    ALOGV("requested jpeg thumbnail size %d x %d", width, height);

    int sizes_cnt = sizeof(THUMBNAIL_SIZES_MAP) / sizeof(cam_dimension_t);
    // Validate thumbnail size
    for (int i = 0; i < sizes_cnt; i++) {
       if (width == THUMBNAIL_SIZES_MAP[i].width &&
           height == THUMBNAIL_SIZES_MAP[i].height) {
           char val[16];
           sprintf(val, "%d", width);
           updateParamEntry(KEY_JPEG_THUMBNAIL_WIDTH, val);
           sprintf(val, "%d", height);
           updateParamEntry(KEY_JPEG_THUMBNAIL_HEIGHT, val);
           return NO_ERROR;
       }
    }
    ALOGE("%s: error: setting jpeg thumbnail size (%d, %d)",
          __func__, width, height);
    return BAD_VALUE;
}

int32_t QCameraParameters::setJpegQuality(const QCameraParameters& params)
{
    int32_t rc = NO_ERROR;
    int quality = params.getInt(KEY_JPEG_QUALITY);
    if (quality >= 0 && quality <= 100) {
        set(KEY_JPEG_QUALITY, quality);
    } else {
        ALOGE("%s: Invalid jpeg quality=%d", __func__, quality);
        rc = BAD_VALUE;
    }

    quality = params.getInt(KEY_JPEG_THUMBNAIL_QUALITY);
    if (quality >= 0 && quality <= 100) {
        char val[16];
        sprintf(val, "%d", quality);
        updateParamEntry(KEY_JPEG_THUMBNAIL_QUALITY, val);
    } else {
        ALOGE("%s: Invalid jpeg thumbnail quality=%d", __func__, quality);
        rc = BAD_VALUE;
    }
    ALOGV("setJpegQuality X");
    return rc;
}

int32_t QCameraParameters::setOrientation(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_ORIENTATION);

    if (str != NULL) {
        if (strcmp(str, portrait) == 0 || strcmp(str, landscape) == 0) {
            // Camera service needs this to decide if the preview frames and raw
            // pictures should be rotated.
            updateParamEntry(KEY_QC_ORIENTATION, str);
        } else {
            ALOGE("%s: Invalid orientation value: %s", __func__, str);
            return BAD_VALUE;
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setAutoExposure(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_AUTO_EXPOSURE);
    const char *prev_str = get(KEY_QC_AUTO_EXPOSURE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setAutoExposure(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setPreviewFpsRange(const QCameraParameters& params)
{
    ALOGV("%s: E", __func__);
    int minFps,maxFps;
    int prevMinFps, prevMaxFps;
    int rc = NO_ERROR;
    bool found = false;

    CameraParameters::getPreviewFpsRange(&prevMinFps, &prevMaxFps);
    ALOGV("%s: Existing FpsRange Values:(%d, %d)", __func__, prevMinFps, prevMaxFps);
    params.getPreviewFpsRange(&minFps, &maxFps);
    ALOGV("%s: Requested FpsRange Values:(%d, %d)", __func__, minFps, maxFps);

    if(minFps == prevMinFps && maxFps == prevMaxFps) {
        ALOGD("%s: No change in FpsRange", __func__);
        rc = NO_ERROR;
        goto end;
    }
    for(int i = 0; i < m_pCapability->fps_ranges_tbl_cnt; i++) {
        // if the value is in the supported list
        if(minFps >= m_pCapability->fps_ranges_tbl[i].min_fps * 1000 &&
           maxFps <= m_pCapability->fps_ranges_tbl[i].max_fps * 1000) {
            found = true;
            ALOGD("%s: FPS i=%d : minFps = %d, maxFps = %d ", __func__, i, minFps, maxFps);
            setPreviewFpsRange(minFps, maxFps);
            break;
        }
    }
    if(found == false){
        ALOGE("%s: error: FPS range value not supported", __func__);
        rc = BAD_VALUE;
    }
end:
    ALOGV("%s: X", __func__);
    return rc;
}

int32_t QCameraParameters::setPreviewFrameRate(const QCameraParameters& params)
{
    ALOGV("%s: E",__func__);
    uint16_t fps = (uint16_t)params.getPreviewFrameRate();
    ALOGV("%s: requested preview frame rate is %d", __func__, fps);
    CameraParameters::setPreviewFrameRate(fps);
    ALOGV("%s: X",__func__);
    return NO_ERROR;
}

int32_t QCameraParameters::setEffect(const QCameraParameters& params)
{
    const char *str = params.get(KEY_EFFECT);
    const char *prev_str = get(KEY_EFFECT);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setEffect(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setFocusMode(const QCameraParameters& params)
{
    const char *str = params.get(KEY_FOCUS_MODE);
    const char *prev_str = get(KEY_FOCUS_MODE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setFocusMode(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setBrightness(const QCameraParameters& params)
{
    int currentBrightness = getInt(KEY_QC_BRIGHTNESS);
    int brightness = params.getInt(KEY_QC_BRIGHTNESS);
    if (currentBrightness !=  brightness) {
        if (brightness >= m_pCapability->brightness_ctrl.min_value &&
            brightness <= m_pCapability->brightness_ctrl.max_value) {
            ALOGV(" new brightness value : %d ", brightness);
            return setBrightness(brightness);
        } else {
            ALOGE("%s: invalid value %d out of (%d, %d)",
                  __func__, brightness,
                  m_pCapability->brightness_ctrl.min_value,
                  m_pCapability->brightness_ctrl.max_value);
            return BAD_VALUE;
        }
    } else {
        ALOGD("%s: No brightness value changed.", __func__);
        return NO_ERROR;
    }
}

int32_t QCameraParameters::setSharpness(const QCameraParameters& params)
{
    int shaprness = params.getInt(KEY_QC_SHARPNESS);
    int prev_sharp = getInt(KEY_QC_SHARPNESS);
    if (prev_sharp !=  shaprness) {
        if((shaprness >= m_pCapability->sharpness_ctrl.min_value) &&
           (shaprness <= m_pCapability->sharpness_ctrl.max_value)) {
            ALOGV(" new sharpness value : %d ", shaprness);
            return setSharpness(shaprness);
        } else {
            ALOGE("%s: invalid value %d out of (%d, %d)",
                  __func__, shaprness,
                  m_pCapability->sharpness_ctrl.min_value,
                  m_pCapability->sharpness_ctrl.max_value);
            return BAD_VALUE;
        }
    } else {
        ALOGD("%s: No value change in shaprness", __func__);
        return NO_ERROR;
    }
}

int32_t QCameraParameters::setSkinToneEnhancement(const QCameraParameters& params)
{
    int sceFactor = params.getInt(KEY_QC_SCE_FACTOR);
    int prev_sceFactor = getInt(KEY_QC_SCE_FACTOR);
    if (prev_sceFactor !=  sceFactor) {
        if((sceFactor >= m_pCapability->sce_ctrl.min_value) &&
           (sceFactor <= m_pCapability->sce_ctrl.max_value)) {
            ALOGV(" new Skintone Enhancement value : %d ", sceFactor);
            return setSkinToneEnhancement(sceFactor);
        } else {
            ALOGE("%s: invalid value %d out of (%d, %d)",
                  __func__, sceFactor,
                  m_pCapability->sce_ctrl.min_value,
                  m_pCapability->sce_ctrl.max_value);
            return BAD_VALUE;
        }
    } else {
        ALOGD("%s: No value change in skintone enhancement factor", __func__);
        return NO_ERROR;
    }
}

int32_t QCameraParameters::setSaturation(const QCameraParameters& params)
{
    int saturation = params.getInt(KEY_QC_SATURATION);
    int prev_sat = getInt(KEY_QC_SATURATION);
    if (prev_sat !=  saturation) {
        if((saturation >= m_pCapability->saturation_ctrl.min_value) &&
           (saturation <= m_pCapability->saturation_ctrl.max_value)) {
            ALOGV(" new saturation value : %d ", saturation);
            return setSaturation(saturation);
        } else {
            ALOGE("%s: invalid value %d out of (%d, %d)",
                  __func__, saturation,
                  m_pCapability->saturation_ctrl.min_value,
                  m_pCapability->saturation_ctrl.max_value);
            return BAD_VALUE;
        }
    } else {
        ALOGD("%s: No value change in saturation factor", __func__);
        return NO_ERROR;
    }
}

int32_t QCameraParameters::setContrast(const QCameraParameters& params)
{
    int contrast = params.getInt(KEY_QC_CONTRAST);
    int prev_contrast = getInt(KEY_QC_CONTRAST);
    if (prev_contrast !=  contrast) {
        if((contrast >= m_pCapability->contrast_ctrl.min_value) &&
           (contrast <= m_pCapability->contrast_ctrl.max_value)) {
            ALOGV(" new contrast value : %d ", contrast);
            int32_t rc = setContrast(contrast);
            return rc;
        } else {
            ALOGE("%s: invalid value %d out of (%d, %d)",
                  __func__, contrast,
                  m_pCapability->contrast_ctrl.min_value,
                  m_pCapability->contrast_ctrl.max_value);
            return BAD_VALUE;
        }
    } else {
        ALOGD("%s: No value change in contrast", __func__);
        return NO_ERROR;
    }
}

int32_t QCameraParameters::setExposureCompensation(const QCameraParameters & params)
{
    int expComp = params.getInt(KEY_EXPOSURE_COMPENSATION);
    int prev_expComp = getInt(KEY_EXPOSURE_COMPENSATION);
    if (prev_expComp !=  expComp) {
        if((expComp >= m_pCapability->exposure_compensation_min) &&
           (expComp <= m_pCapability->exposure_compensation_max)) {
            ALOGV(" new Exposure Compensation value : %d ", expComp);
            return setExposureCompensation(expComp);
        } else {
            ALOGE("%s: invalid value %d out of (%d, %d)",
                  __func__, expComp,
                  m_pCapability->exposure_compensation_min,
                  m_pCapability->exposure_compensation_max);
            return BAD_VALUE;
        }
    } else {
        ALOGD("%s: No value change in Exposure Compensation", __func__);
        return NO_ERROR;
    }
}

int32_t QCameraParameters::setWhiteBalance(const QCameraParameters& params)
{
    const char *str = params.get(KEY_WHITE_BALANCE);
    const char *prev_str = get(KEY_WHITE_BALANCE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setWhiteBalance(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setAntibanding(const QCameraParameters& params)
{
    const char *str = params.get(KEY_ANTIBANDING);
    const char *prev_str = get(KEY_ANTIBANDING);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setAntibanding(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setSceneDetect(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_SCENE_DETECT);
    const char *prev_str = get(KEY_QC_SCENE_DETECT);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setSceneDetect(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setZoom(const QCameraParameters& params)
{
    if ((m_pCapability->zoom_supported == 0 ||
         m_pCapability->zoom_ratio_tbl_cnt == 0)) {
        ALOGD("%s: no zoom support", __func__);
        return NO_ERROR;
    }

    int zoomLevel = params.getInt(KEY_ZOOM);
    if((zoomLevel < 0) ||
       (zoomLevel >= m_pCapability->zoom_ratio_tbl_cnt)) {
        ALOGE("%s: invalid value %d out of (%d, %d)",
              __func__, zoomLevel,
              0, m_pCapability->zoom_ratio_tbl_cnt-1);
        return BAD_VALUE;
    }

    int prevZoomLevel = getInt(KEY_ZOOM);
    if (prevZoomLevel == zoomLevel) {
        ALOGD("%s: No value change in contrast", __func__);
        return NO_ERROR;
    }

    return setZoom(zoomLevel);
}

int32_t  QCameraParameters::setISOValue(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_ISO_MODE);
    const char *prev_str = get(KEY_QC_ISO_MODE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setISOValue(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setRotation(const QCameraParameters& params)
{
    int rotation = params.getInt(KEY_ROTATION);
    if (rotation != -1) {
        if (rotation == 0 || rotation == 90 ||
            rotation == 180 || rotation == 270) {
            set(KEY_ROTATION, rotation);
        } else {
            ALOGE("Invalid rotation value: %d", rotation);
            return BAD_VALUE;
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setFlash(const QCameraParameters& params)
{
    const char *str = params.get(KEY_FLASH_MODE);
    const char *prev_str = get(KEY_FLASH_MODE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setFlash(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setAecLock(const QCameraParameters& params)
{
    const char *str = params.get(KEY_AUTO_EXPOSURE_LOCK);
    const char *prev_str = get(KEY_AUTO_EXPOSURE_LOCK);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setAecLock(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setAwbLock(const QCameraParameters& params)
{
    const char *str = params.get(KEY_AUTO_WHITEBALANCE_LOCK);
    const char *prev_str = get(KEY_AUTO_WHITEBALANCE_LOCK);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setAwbLock(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setMCEValue(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_MEMORY_COLOR_ENHANCEMENT);
    const char *prev_str = get(KEY_QC_MEMORY_COLOR_ENHANCEMENT);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setMCEValue(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setHighFrameRate(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_VIDEO_HIGH_FRAME_RATE);
    const char *prev_str = get(KEY_QC_VIDEO_HIGH_FRAME_RATE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setHighFrameRate(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setLensShadeValue(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_LENSSHADE);
    const char *prev_str = get(KEY_QC_LENSSHADE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setLensShadeValue(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setFocusAreas(const QCameraParameters& params)
{
    const char *str = params.get(KEY_FOCUS_AREAS);
    if (str != NULL) {
        int max_num_af_areas = getInt(KEY_MAX_NUM_FOCUS_AREAS);
        if(max_num_af_areas == 0) {
            ALOGE("%s: max num of AF area is 0, cannot set focus areas", __func__);
            return BAD_VALUE;
        }

        const char *prev_str = get(KEY_FOCUS_AREAS);
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setFocusAreas(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setMeteringAreas(const QCameraParameters& params)
{
    const char *str = params.get(KEY_METERING_AREAS);
    if (str != NULL) {
        int max_num_mtr_areas = getInt(KEY_MAX_NUM_METERING_AREAS);
        if(max_num_mtr_areas == 0) {
            ALOGE("%s: max num of metering areas is 0, cannot set focus areas", __func__);
            return BAD_VALUE;
        }

        const char *prev_str = get(KEY_METERING_AREAS);
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setMeteringAreas(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setSceneMode(const QCameraParameters& params)
{
    const char *str = params.get(KEY_SCENE_MODE);
    const char *prev_str = get(KEY_SCENE_MODE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setMeteringAreas(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setSelectableZoneAf(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_SELECTABLE_ZONE_AF);
    const char *prev_str = get(KEY_QC_SELECTABLE_ZONE_AF);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setSelectableZoneAf(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setAEBracket(const QCameraParameters& params)
{
    const char *expStr = params.get(KEY_QC_CAPTURE_BURST_EXPOSURE);
    if (NULL != expStr) {
        set(KEY_QC_CAPTURE_BURST_EXPOSURE, expStr);
    } else {
        remove(KEY_QC_CAPTURE_BURST_EXPOSURE);
    }

    const char *str = params.get(KEY_QC_AE_BRACKET_HDR);
    const char *prev_str = get(KEY_QC_AE_BRACKET_HDR);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setAEBracket(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setRedeyeReduction(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_REDEYE_REDUCTION);
    const char *prev_str = get(KEY_QC_REDEYE_REDUCTION);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setRedeyeReduction(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setGpsLocation(const QCameraParameters& params)
{
    const char *method = params.get(KEY_GPS_PROCESSING_METHOD);
    if (method) {
        set(KEY_GPS_PROCESSING_METHOD, method);
    }else {
        remove(KEY_GPS_PROCESSING_METHOD);
    }

    const char *latitude = params.get(KEY_GPS_LATITUDE);
    if (latitude) {
        set(KEY_GPS_LATITUDE, latitude);
    }else {
        remove(KEY_GPS_LATITUDE);
    }

    const char *latitudeRef = params.get(KEY_QC_GPS_LATITUDE_REF);
    if (latitudeRef) {
        set(KEY_QC_GPS_LATITUDE_REF, latitudeRef);
    }else {
        remove(KEY_QC_GPS_LATITUDE_REF);
    }

    const char *longitude = params.get(KEY_GPS_LONGITUDE);
    if (longitude) {
        set(KEY_GPS_LONGITUDE, longitude);
    }else {
        remove(KEY_GPS_LONGITUDE);
    }

    const char *longitudeRef = params.get(KEY_QC_GPS_LONGITUDE_REF);
    if (longitudeRef) {
        set(KEY_QC_GPS_LONGITUDE_REF, longitudeRef);
    }else {
        remove(KEY_QC_GPS_LONGITUDE_REF);
    }

    const char *altitudeRef = params.get(KEY_QC_GPS_ALTITUDE_REF);
    if (altitudeRef) {
        set(KEY_QC_GPS_ALTITUDE_REF, altitudeRef);
    }else {
        remove(KEY_QC_GPS_ALTITUDE_REF);
    }

    const char *altitude = params.get(KEY_GPS_ALTITUDE);
    if (altitude) {
        set(KEY_GPS_ALTITUDE, altitude);
    }else {
        remove(KEY_GPS_ALTITUDE);
    }

    const char *status = params.get(KEY_QC_GPS_STATUS);
    if (status) {
        set(KEY_QC_GPS_STATUS, status);
    } else {
        remove(KEY_QC_GPS_STATUS);
    }

    const char *timestamp = params.get(KEY_GPS_TIMESTAMP);
    if (timestamp) {
        set(KEY_GPS_TIMESTAMP, timestamp);
    }else {
        remove(KEY_GPS_TIMESTAMP);
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setNumOfSnapshot(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_NUM_SNAPSHOT_PER_SHUTTER);
    if (str != NULL) {
        updateParamEntry(KEY_QC_NUM_SNAPSHOT_PER_SHUTTER, str);
    } else {
        updateParamEntry(KEY_QC_NUM_SNAPSHOT_PER_SHUTTER, "1");
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setRecordingHint(const QCameraParameters& params)
{
    const char * str = params.get(KEY_RECORDING_HINT);
    const char *prev_str = get(KEY_RECORDING_HINT);
    if (str != NULL) {
        if (prev_str == NULL || strcmp(str, prev_str) != 0) {
            int32_t value = lookupAttr(TRUE_FALSE_MODES_MAP,
                                       sizeof(TRUE_FALSE_MODES_MAP)/sizeof(QCameraMap),
                                       str);
            if(value != NAME_NOT_FOUND){
                updateParamEntry(KEY_RECORDING_HINT, str);
                setRecordingHintValue(value);
                return NO_ERROR;
            } else {
                ALOGE("Invalid recording hint value: %s", str);
                return BAD_VALUE;
            }
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setNoDisplayMode(const QCameraParameters& params)
{
    const char *str_val  = params.get(KEY_QC_NO_DISPLAY_MODE);
    const char *prev_str = get(KEY_QC_NO_DISPLAY_MODE);
    if(str_val && strlen(str_val) > 0) {
        if (prev_str == NULL || strcmp(str_val, prev_str) != 0) {
            m_bNoDisplayMode = atoi(str_val);
            updateParamEntry(KEY_QC_NO_DISPLAY_MODE, str_val);
            m_bNeedRestart = true;
        }
    } else {
        m_bNoDisplayMode = false;
    }
    ALOGD("Param m_bNoDisplayMode = %d", m_bNoDisplayMode);
    return NO_ERROR;
}

int32_t QCameraParameters::setZslMode(const QCameraParameters& params)
{
    const char *str_val  = params.get(KEY_QC_ZSL);
    const char *prev_val  = get(KEY_QC_ZSL);

    if (str_val != NULL) {
        if (prev_val == NULL || strcmp(str_val, prev_val) != 0) {
            int32_t value = lookupAttr(ON_OFF_MODES_MAP,
                                       sizeof(ON_OFF_MODES_MAP)/sizeof(QCameraMap),
                                       str_val);
            if (value != NAME_NOT_FOUND) {
                updateParamEntry(KEY_QC_ZSL, str_val);
                m_bZslMode = (value > 0)? true : false;

                // ZSL mode changed, need restart preview
                m_bNeedRestart = true;
            } else {
                ALOGE("Invalid ZSL mode value: %s", str_val);
                return BAD_VALUE;
            }
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setWaveletDenoise(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_DENOISE);
    const char *prev_str = get(KEY_QC_DENOISE);
    if (str != NULL) {
        if (prev_str == NULL ||
            strcmp(str, prev_str) != 0) {
            return setWaveletDenoise(str);
        }
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setCameraMode(const QCameraParameters& params)
{
    const char *str = params.get(KEY_QC_CAMERA_MODE);
    if (str != NULL) {
        set(KEY_QC_CAMERA_MODE, str);
    } else {
        remove(KEY_QC_CAMERA_MODE);
    }
    return NO_ERROR;
}

int32_t QCameraParameters::setZslAttributes(const QCameraParameters& params)
{
    // TODO: may switch to pure param instead of sysprop
    char prop[32];

    const char *str = params.get(KEY_QC_ZSL_BURST_INTERVAL);
    if (str != NULL) {
        set(KEY_QC_ZSL_BURST_INTERVAL, str);
    } else {
        memset(prop, 0, sizeof(prop));
        property_get("persist.camera.zsl.interval", prop, "1");
        set(KEY_QC_ZSL_BURST_INTERVAL, prop);
    }

    str = params.get(KEY_QC_ZSL_BURST_LOOKBACK);
    if (str != NULL) {
        set(KEY_QC_ZSL_BURST_LOOKBACK, str);
    } else {
        memset(prop, 0, sizeof(prop));
        property_get("persist.camera.zsl.backlookcnt", prop, "2");
        set(KEY_QC_ZSL_BURST_LOOKBACK, prop);
    }

    str = params.get(KEY_QC_ZSL_QUEUE_DEPTH);
    if (str != NULL) {
        set(KEY_QC_ZSL_QUEUE_DEPTH, str);
    } else {
        memset(prop, 0, sizeof(prop));
        property_get("persist.camera.zsl.queuedepth", prop, "2");
        set(KEY_QC_ZSL_QUEUE_DEPTH, prop);
    }

    return NO_ERROR;
}

int32_t QCameraParameters::updateParameters(QCameraParameters& params,
                                            bool &needRestart)
{
    int32_t final_rc = NO_ERROR;
    int32_t rc;
    m_bNeedRestart = false;

    if(initBatchUpdate(m_pParamBuf) < 0 ) {
        ALOGE("%s:Failed to initialize group update table",__func__);
        rc = BAD_TYPE;
        goto UPDATE_PARAM_DONE;
    }

    if ((rc = setPreviewSize(params)))                  final_rc = rc;
    if ((rc = setVideoSize(params)))                    final_rc = rc;
    if ((rc = setPictureSize(params)))                  final_rc = rc;
    if ((rc = setPreviewFormat(params)))                final_rc = rc;
    if ((rc = setPictureFormat(params)))                final_rc = rc;
    if ((rc = setJpegThumbnailSize(params)))            final_rc = rc;
    if ((rc = setJpegQuality(params)))                  final_rc = rc;
    if ((rc = setOrientation(params)))                  final_rc = rc;
    if ((rc = setRotation(params)))                     final_rc = rc;
    if ((rc = setNoDisplayMode(params)))                final_rc = rc;
    if ((rc = setZslMode(params)))                      final_rc = rc;
    if ((rc = setZslAttributes(params)))                final_rc = rc;
    if ((rc = setCameraMode(params)))                   final_rc = rc;
    if ((rc = setRecordingHint(params)))                final_rc = rc;

    if ((rc = setPreviewFpsRange(params)))              final_rc = rc;
    if ((rc = setPreviewFrameRate(params)))             final_rc = rc;
    if ((rc = setAutoExposure(params)))                 final_rc = rc;
    if ((rc = setEffect(params)))                       final_rc = rc;
    if ((rc = setBrightness(params)))                   final_rc = rc;
    if ((rc = setZoom(params)))                         final_rc = rc;
    if ((rc = setSharpness(params)))                    final_rc = rc;
    if ((rc = setSaturation(params)))                   final_rc = rc;
    if ((rc = setContrast(params)))                     final_rc = rc;
    if ((rc = setFocusMode(params)))                    final_rc = rc;
    if ((rc = setISOValue(params)))                     final_rc = rc;
    if ((rc = setSkinToneEnhancement(params)))          final_rc = rc;
    if ((rc = setFlash(params)))                        final_rc = rc;
    if ((rc = setAecLock(params)))                      final_rc = rc;
    if ((rc = setAwbLock(params)))                      final_rc = rc;
    if ((rc = setLensShadeValue(params)))               final_rc = rc;
    if ((rc = setMCEValue(params)))                     final_rc = rc;
    if ((rc = setHighFrameRate(params)))                final_rc = rc;
    if ((rc = setAntibanding(params)))                  final_rc = rc;
    if ((rc = setExposureCompensation(params)))         final_rc = rc;
    if ((rc = setWhiteBalance(params)))                 final_rc = rc;
    if ((rc = setSceneMode(params)))                    final_rc = rc;
    if ((rc = setFocusAreas(params)))                   final_rc = rc;
    if ((rc = setMeteringAreas(params)))                final_rc = rc;
    if ((rc = setSelectableZoneAf(params)))             final_rc = rc;
    if ((rc = setRedeyeReduction(params)))              final_rc = rc;
    if ((rc = setAEBracket(params)))                    final_rc = rc;
    if ((rc = setGpsLocation(params)))                  final_rc = rc;
    if ((rc = setNumOfSnapshot(params)))                final_rc = rc;
    if ((rc = setWaveletDenoise(params)))               final_rc = rc;

UPDATE_PARAM_DONE:
    needRestart = m_bNeedRestart;
    return final_rc;
}

int32_t QCameraParameters::commitParameters()
{
    return commitSetBatch();
}

int32_t QCameraParameters::initDefaultParameters()
{
    int32_t rc = NO_ERROR;

    if(initBatchUpdate(m_pParamBuf) < 0 ) {
        ALOGE("%s:Failed to initialize group update table", __func__);
        return BAD_TYPE;
    }

    /*************************Initialize Values******************************/
    // Set read only parameters from camera capability
    set(KEY_SMOOTH_ZOOM_SUPPORTED,
        m_pCapability->smooth_zoom_supported? VALUE_TRUE : VALUE_FALSE);
    set(KEY_ZOOM_SUPPORTED,
        m_pCapability->zoom_supported? VALUE_TRUE : VALUE_FALSE);
    set(KEY_VIDEO_SNAPSHOT_SUPPORTED,
        m_pCapability->video_snapshot_supported? VALUE_TRUE : VALUE_FALSE);
    set(KEY_VIDEO_STABILIZATION_SUPPORTED,
        m_pCapability->video_stablization_supported? VALUE_TRUE : VALUE_FALSE);
    set(KEY_AUTO_EXPOSURE_LOCK_SUPPORTED,
        m_pCapability->auto_exposure_lock_supported? VALUE_TRUE : VALUE_FALSE);
    set(KEY_AUTO_WHITEBALANCE_LOCK_SUPPORTED,
        m_pCapability->auto_wb_lock_supported? VALUE_TRUE : VALUE_FALSE);
    set(KEY_QC_SUPPORTED_CAMERA_FEATURES,
        m_pCapability->qcom_supported_feature_mask);
    set(KEY_MAX_NUM_DETECTED_FACES_HW, 0);
    set(KEY_MAX_NUM_DETECTED_FACES_SW, m_pCapability->max_num_roi);
    set(KEY_QC_MAX_NUM_REQUESTED_FACES, m_pCapability->max_num_roi);
    // Set focal length, horizontal view angle, and vertical view angle
    setFloat(KEY_FOCAL_LENGTH, m_pCapability->focal_length);
    setFloat(KEY_HORIZONTAL_VIEW_ANGLE, m_pCapability->hor_view_angle);
    setFloat(KEY_VERTICAL_VIEW_ANGLE, m_pCapability->ver_view_angle);

    // Set supported preview sizes
    if (m_pCapability->preview_sizes_tbl_cnt > 0) {
        String8 previewSizeValues = createSizesString(
                m_pCapability->preview_sizes_tbl, m_pCapability->preview_sizes_tbl_cnt);
        set(KEY_SUPPORTED_PREVIEW_SIZES, previewSizeValues.string());
        ALOGD("%s: supported preview sizes: %s", __func__, previewSizeValues.string());
        // Set default preview size
        CameraParameters::setPreviewSize(m_pCapability->preview_sizes_tbl[0].width,
                                         m_pCapability->preview_sizes_tbl[0].height);
    } else {
        ALOGE("%s: supported preview sizes cnt is 0!!!", __func__);
    }

    // Set supported video sizes
    if (m_pCapability->video_sizes_tbl_cnt > 0) {
        String8 videoSizeValues = createSizesString(
                m_pCapability->video_sizes_tbl, m_pCapability->video_sizes_tbl_cnt);
        set(KEY_SUPPORTED_VIDEO_SIZES, videoSizeValues.string());
        ALOGD("%s: supported video sizes: %s", __func__, videoSizeValues.string());
        // Set default video size
        CameraParameters::setVideoSize(m_pCapability->video_sizes_tbl[0].width,
                                       m_pCapability->video_sizes_tbl[0].height);

        //Set preferred Preview size for video
        String8 vSize = createSizesString(&m_pCapability->video_sizes_tbl[0], 1);
        set(KEY_PREFERRED_PREVIEW_SIZE_FOR_VIDEO, vSize.string());
    } else {
        ALOGE("%s: supported video sizes cnt is 0!!!", __func__);
    }

    // Set supported picture sizes
    if (m_pCapability->picture_sizes_tbl_cnt) {
        String8 pictureSizeValues = createSizesString(
                m_pCapability->picture_sizes_tbl, m_pCapability->picture_sizes_tbl_cnt);
        set(KEY_SUPPORTED_PICTURE_SIZES, pictureSizeValues.string());
        ALOGD("%s: supported pic sizes: %s", __func__, pictureSizeValues.string());
        // Set default picture size
        CameraParameters::setPictureSize(m_pCapability->picture_sizes_tbl[0].width,
                       m_pCapability->picture_sizes_tbl[0].height);
    } else {
        ALOGE("%s: supported picture sizes cnt is 0!!!", __func__);
    }

    // Set supported thumbnail sizes
    String8 thumbnailSizeValues = createSizesString(
            THUMBNAIL_SIZES_MAP,
            sizeof(THUMBNAIL_SIZES_MAP)/sizeof(cam_dimension_t));
    set(KEY_SUPPORTED_JPEG_THUMBNAIL_SIZES, thumbnailSizeValues.string());
    // Set default thumnail size
    set(KEY_JPEG_THUMBNAIL_WIDTH, THUMBNAIL_SIZES_MAP[0].width);
    set(KEY_JPEG_THUMBNAIL_HEIGHT, THUMBNAIL_SIZES_MAP[0].height);

    // Set supported preview formats
    String8 previewFormatValues = createValuesString(
            (int *)m_pCapability->supported_preview_fmts,
            m_pCapability->supported_preview_fmt_cnt,
            PREVIEW_FORMATS_MAP,
            sizeof(PREVIEW_FORMATS_MAP)/sizeof(QCameraMap));
    set(KEY_SUPPORTED_PREVIEW_FORMATS, previewFormatValues.string());
    // Set default preview format
    CameraParameters::setPreviewFormat(PIXEL_FORMAT_YUV420SP);

    // Set default Video Format
    set(KEY_VIDEO_FRAME_FORMAT, PIXEL_FORMAT_YUV420SP);

    // Set supported picture formats
    String8 pictureTypeValues(PIXEL_FORMAT_JPEG);
    String8 str = createValuesString(
            (int *)m_pCapability->supported_raw_fmts,
            m_pCapability->supported_raw_fmt_cnt,
            PICTURE_TYPES_MAP,
            sizeof(PICTURE_TYPES_MAP)/sizeof(QCameraMap));
    if (str.string() != NULL) {
        pictureTypeValues.append(",");
        pictureTypeValues.append(str);
    }

    set(KEY_SUPPORTED_PICTURE_FORMATS, pictureTypeValues.string());
    // Set default picture Format
    CameraParameters::setPictureFormat(PIXEL_FORMAT_JPEG);
    // Set raw image size
    char raw_size_str[32];
    snprintf(raw_size_str, sizeof(raw_size_str), "%dx%d",
             m_pCapability->raw_dim.width, m_pCapability->raw_dim.height);
    set(KEY_QC_RAW_PICUTRE_SIZE, raw_size_str);

    //set default jpeg quality and thumbnail quality
    set(KEY_JPEG_QUALITY, 85);
    set(KEY_JPEG_THUMBNAIL_QUALITY, 85);

    // Set FPS ranges
    if (m_pCapability->fps_ranges_tbl_cnt > 0) {
        String8 fpsRangeValues = createFpsRangeString(m_pCapability->fps_ranges_tbl,
                                                      m_pCapability->fps_ranges_tbl_cnt);
        set(KEY_SUPPORTED_PREVIEW_FPS_RANGE, fpsRangeValues.string());
        setPreviewFpsRange(int(m_pCapability->fps_ranges_tbl[0].min_fps * 1000),
                           int(m_pCapability->fps_ranges_tbl[0].max_fps * 1000));

        // Set legacy preview fps
        String8 fpsValues = createFpsString(m_pCapability->fps_ranges_tbl,
                                            m_pCapability->fps_ranges_tbl_cnt);
        set(KEY_SUPPORTED_PREVIEW_FRAME_RATES, fpsValues.string());
        CameraParameters::setPreviewFrameRate(
           (int)(m_pCapability->fps_ranges_tbl[0].max_fps * 1000));
    } else {
        ALOGE("%s: supported fps ranges cnt is 0!!!", __func__);
    }

    // Set supported focus modes
    if (m_pCapability->supported_focus_modes_cnt > 0) {
        String8 focusModeValues = createValuesString(
                (int *)m_pCapability->supported_focus_modes,
                m_pCapability->supported_focus_modes_cnt,
                FOCUS_MODES_MAP,
                sizeof(FOCUS_MODES_MAP)/sizeof(QCameraMap));
        set(KEY_SUPPORTED_FOCUS_MODES, focusModeValues);

        // Set default focus mode and update corresponding parameter buf
        setFocusMode(FOCUS_MODE_INFINITY); //TODO: change to FOCUS_MODE_AUTO
    } else {
        ALOGE("%s: supported focus modes cnt is 0!!!", __func__);
    }

    // Set focus areas
    set(KEY_MAX_NUM_FOCUS_AREAS, m_pCapability->max_num_focus_areas);
    if (m_pCapability->max_num_focus_areas > 0) {
        setFocusAreas(DEFAULT_CAMERA_AREA);
    }

    // Set metering areas
    set(KEY_MAX_NUM_METERING_AREAS, m_pCapability->max_num_metering_areas);
    if (m_pCapability->max_num_metering_areas > 0) {
        setMeteringAreas(DEFAULT_CAMERA_AREA);
    }

    // Set Saturation
    set(KEY_QC_MIN_SATURATION, m_pCapability->saturation_ctrl.min_value);
    set(KEY_QC_MAX_SATURATION, m_pCapability->saturation_ctrl.max_value);
    set(KEY_QC_SATURATION_STEP, m_pCapability->saturation_ctrl.step);
    setSaturation(m_pCapability->saturation_ctrl.def_value);

    // Set Sharpness
    set(KEY_QC_MIN_SHARPNESS, m_pCapability->sharpness_ctrl.min_value);
    set(KEY_QC_MAX_SHARPNESS, m_pCapability->sharpness_ctrl.max_value);
    set(KEY_QC_SHARPNESS_STEP, m_pCapability->sharpness_ctrl.step);
    setSharpness(m_pCapability->sharpness_ctrl.def_value);

    // Set Contrast
    set(KEY_QC_MIN_CONTRAST, m_pCapability->contrast_ctrl.min_value);
    set(KEY_QC_MAX_CONTRAST, m_pCapability->contrast_ctrl.max_value);
    set(KEY_QC_CONTRAST_STEP, m_pCapability->contrast_ctrl.step);
    setContrast(m_pCapability->contrast_ctrl.def_value);

    // Set SCE factor
    set(KEY_QC_MIN_SCE_FACTOR, m_pCapability->sce_ctrl.min_value); // -10
    set(KEY_QC_MAX_SCE_FACTOR, m_pCapability->sce_ctrl.max_value); // 10
    set(KEY_QC_SCE_FACTOR_STEP, m_pCapability->sce_ctrl.step);     // 10
    setSkinToneEnhancement(m_pCapability->sce_ctrl.def_value);     // 0

    // Set Brightness
    set(KEY_QC_MIN_BRIGHTNESS, m_pCapability->brightness_ctrl.min_value); // 0
    set(KEY_QC_MAX_BRIGHTNESS, m_pCapability->brightness_ctrl.max_value); // 6
    set(KEY_QC_BRIGHTNESS_STEP, m_pCapability->brightness_ctrl.step);     // 1
    setBrightness(m_pCapability->brightness_ctrl.def_value);

    // Set Auto exposure
    String8 autoExposureValues = createValuesString(
            (int *)m_pCapability->supported_aec_modes,
            m_pCapability->supported_aec_modes_cnt,
            AUTO_EXPOSURE_MAP,
            sizeof(AUTO_EXPOSURE_MAP) / sizeof(QCameraMap));
    set(KEY_QC_SUPPORTED_AUTO_EXPOSURE, autoExposureValues.string());
    setAutoExposure(AUTO_EXPOSURE_FRAME_AVG);

    // Set Exposure Compensation
    set(KEY_MAX_EXPOSURE_COMPENSATION, m_pCapability->exposure_compensation_max); // 12
    set(KEY_MIN_EXPOSURE_COMPENSATION, m_pCapability->exposure_compensation_min); // -12
    setFloat(KEY_EXPOSURE_COMPENSATION_STEP, m_pCapability->exposure_compensation_step); // 1/6
    setExposureCompensation(m_pCapability->exposure_compensation_default); // 0

    // Set Antibanding
    String8 antibandingValues = createValuesString(
            (int *)m_pCapability->supported_antibandings,
            m_pCapability->supported_antibandings_cnt,
            ANTIBANDING_MODES_MAP,
            sizeof(ANTIBANDING_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_SUPPORTED_ANTIBANDING, antibandingValues);
    setAntibanding(ANTIBANDING_OFF);

    // Set Effect
    String8 effectValues = createValuesString(
            (int *)m_pCapability->supported_effects,
            m_pCapability->supported_effects_cnt,
            EFFECT_MODES_MAP,
            sizeof(EFFECT_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_SUPPORTED_EFFECTS, effectValues);
    setEffect(EFFECT_NONE);

    // Set WhiteBalance
    String8 whitebalanceValues = createValuesString(
            (int *)m_pCapability->supported_white_balances,
            m_pCapability->supported_white_balances_cnt,
            WHITE_BALANCE_MODES_MAP,
            sizeof(WHITE_BALANCE_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_SUPPORTED_WHITE_BALANCE, whitebalanceValues);
    setWhiteBalance(WHITE_BALANCE_AUTO);

    // Set Flash mode
    String8 flashValues = createValuesString(
            (int *)m_pCapability->supported_flash_modes,
            m_pCapability->supported_flash_modes_cnt,
            FLASH_MODES_MAP,
            sizeof(FLASH_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_SUPPORTED_FLASH_MODES, flashValues);
    setFlash(FLASH_MODE_OFF);

    // Set Scene Mode
    String8 sceneModeValues = createValuesString(
            (int *)m_pCapability->supported_scene_modes,
            m_pCapability->supported_scene_modes_cnt,
            SCENE_MODES_MAP,
            sizeof(SCENE_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_SUPPORTED_SCENE_MODES, sceneModeValues);
    setSceneMode(SCENE_MODE_AUTO);

    // Set ISO Mode
    String8 isoValues = createValuesString(
            (int *)m_pCapability->supported_iso_modes,
            m_pCapability->supported_iso_modes_cnt,
            ISO_MODES_MAP,
            sizeof(ISO_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_QC_SUPPORTED_ISO_MODES, isoValues);
    setISOValue(ISO_AUTO);

    // Set HFR
    String8 hfrValues = createHfrValuesString(
            m_pCapability->hfr_tbl,
            m_pCapability->hfr_tbl_cnt,
            HFR_MODES_MAP,
            sizeof(HFR_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_QC_SUPPORTED_VIDEO_HIGH_FRAME_RATE_MODES, hfrValues.string());
    String8 hfrSizeValues = createHfrSizesString(
            m_pCapability->hfr_tbl,
            m_pCapability->hfr_tbl_cnt);
    set(KEY_QC_SUPPORTED_HFR_SIZES, hfrSizeValues.string());
    setHighFrameRate(VIDEO_HFR_OFF);

    // Set Focus algorithms
    String8 focusAlgoValues = createValuesString(
            (int *)m_pCapability->supported_focus_algos,
            m_pCapability->supported_focus_algos_cnt,
            FOCUS_ALGO_MAP,
            sizeof(FOCUS_ALGO_MAP) / sizeof(QCameraMap));
    set(KEY_QC_SUPPORTED_FOCUS_ALGOS, focusAlgoValues);
    setSelectableZoneAf(FOCUS_ALGO_AUTO);

    // Set Zoom Ratios
    if (m_pCapability->zoom_supported > 0) {
        String8 zoomRatioValues = createZoomRatioValuesString(
                m_pCapability->zoom_ratio_tbl,
                m_pCapability->zoom_ratio_tbl_cnt);
        set(KEY_ZOOM_RATIOS, zoomRatioValues);
        set(KEY_MAX_ZOOM, m_pCapability->zoom_ratio_tbl_cnt - 1);
        setZoom(0);
    }

    // Set Bracketing/HDR
    String8 bracketingValues = createValuesStringFromMap(
            HDR_BRACKETING_MODES_MAP,
            sizeof(HDR_BRACKETING_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_QC_SUPPORTED_AE_BRACKET_HDR_MODES, bracketingValues);
    setAEBracket(AE_BRACKET_HDR_OFF);

    // Set Denoise
    String8 denoiseValues = createValuesStringFromMap(
       DENOISE_ON_OFF_MODES_MAP, sizeof(DENOISE_ON_OFF_MODES_MAP) / sizeof(QCameraMap));
    set(KEY_QC_SUPPORTED_DENOISE, denoiseValues.string());
    setWaveletDenoise(DENOISE_OFF);

    // Set feature enable/disable
    String8 enableDisableValues = createValuesStringFromMap(
        ENABLE_DISABLE_MODES_MAP, sizeof(ENABLE_DISABLE_MODES_MAP) / sizeof(QCameraMap));

    // Set Lens Shading
    set(KEY_QC_SUPPORTED_LENSSHADE_MODES, enableDisableValues);
    setLensShadeValue(VALUE_ENABLE);

    // Set MCE
    set(KEY_QC_SUPPORTED_MEM_COLOR_ENHANCE_MODES, enableDisableValues);
    setMCEValue(VALUE_ENABLE);

    // Set Histogram
    set(KEY_QC_SUPPORTED_HISTOGRAM_MODES, enableDisableValues);
    set(KEY_QC_HISTOGRAM, VALUE_DISABLE);

    //Set Red Eye Reduction
    set(KEY_QC_SUPPORTED_REDEYE_REDUCTION, enableDisableValues);
    setRedeyeReduction(VALUE_DISABLE);

    // Set feature on/off
    String8 onOffValues = createValuesStringFromMap(
        ON_OFF_MODES_MAP, sizeof(ON_OFF_MODES_MAP) / sizeof(QCameraMap));

    //Set Scene Detection
    set(KEY_QC_SUPPORTED_SCENE_DETECT, onOffValues);
    setSceneDetect(VALUE_OFF);

    //Set Face Detection
    set(KEY_QC_SUPPORTED_FACE_DETECTION, onOffValues);
    set(KEY_QC_FACE_DETECTION, VALUE_OFF);

    //Set ZSL
    set(KEY_QC_SUPPORTED_ZSL_MODES, onOffValues);

    //Set Touch AF/AEC
    set(KEY_QC_SUPPORTED_TOUCH_AF_AEC, onOffValues);
    set(KEY_QC_TOUCH_AF_AEC, VALUE_OFF);

    // Set default Auto Exposure lock value
    setAecLock(VALUE_FALSE);

    //Set default AWB_LOCK lock value
    setAwbLock(VALUE_FALSE);

    // Set default Camera mode
    set(KEY_QC_CAMERA_MODE, 0);

    commitSetBatch();

    return rc;
}

int32_t QCameraParameters::init(cam_capability_t *capabilities, mm_camera_vtbl_t *mmOps)
{
    int32_t rc = NO_ERROR;

    m_pCapability = capabilities;
    m_pCamOpsTbl = mmOps;

    //Allocate Set Param Buffer
    m_pParamHeap = new QCameraHeapMemory();
    rc = m_pParamHeap->allocate(1, sizeof(parm_buffer_t));
    if(rc != OK) {
        rc = NO_MEMORY;
        ALOGE("Failed to allocate SETPARM Heap memory");
        goto TRANS_INIT_ERROR1;
    }

    //Map memory for parameters buffer
    rc = m_pCamOpsTbl->ops->map_buf(m_pCamOpsTbl->camera_handle,
                             CAM_MAPPING_BUF_TYPE_PARM_BUF,
                             m_pParamHeap->getFd(0),
                             sizeof(parm_buffer_t));
    if(rc < 0) {
        ALOGE("%s:failed to map SETPARM buffer",__func__);
        rc = FAILED_TRANSACTION;
        goto TRANS_INIT_ERROR2;
    }
    m_pParamBuf = (parm_buffer_t*) DATA_PTR(m_pParamHeap,0);

    initDefaultParameters();

    goto TRANS_INIT_DONE;

TRANS_INIT_ERROR2:
    m_pParamHeap->deallocate();

TRANS_INIT_ERROR1:
    delete m_pParamHeap;
    m_pParamHeap = NULL;

TRANS_INIT_DONE:
    return rc;
}

void QCameraParameters::deinit()
{
    //clear all entries in the map
    String8 emptyStr;
    QCameraParameters::unflatten(emptyStr);

    if (NULL != m_pCamOpsTbl) {
        m_pCamOpsTbl->ops->unmap_buf(
                             m_pCamOpsTbl->camera_handle,
                             CAM_MAPPING_BUF_TYPE_PARM_BUF);
        m_pCamOpsTbl = NULL;
    }
    m_pCapability = NULL;
    if (NULL != m_pParamHeap) {
        m_pParamHeap->deallocate();
        delete m_pParamHeap;
        m_pParamHeap = NULL;
        m_pParamBuf = NULL;
    }

    m_tempMap.clear();
}

// Parse string like "640x480" or "10000,20000"
int32_t QCameraParameters::parse_pair(const char *str,
                                      int *first,
                                      int *second,
                                      char delim,
                                      char **endptr = NULL)
{
    // Find the first integer.
    char *end;
    int w = (int)strtol(str, &end, 10);
    // If a delimeter does not immediately follow, give up.
    if (*end != delim) {
        ALOGE("Cannot find delimeter (%c) in str=%s", delim, str);
        return BAD_VALUE;
    }

    // Find the second integer, immediately after the delimeter.
    int h = (int)strtol(end+1, &end, 10);

    *first = w;
    *second = h;

    if (endptr) {
        *endptr = end;
    }

    return NO_ERROR;
}

void QCameraParameters::parseSizesList(const char *sizesStr, Vector<Size> &sizes)
{
    if (sizesStr == 0) {
        return;
    }

    char *sizeStartPtr = (char *)sizesStr;

    while (true) {
        int width, height;
        int success = parse_pair(sizeStartPtr, &width, &height, 'x',
                                 &sizeStartPtr);
        if (success == -1 || (*sizeStartPtr != ',' && *sizeStartPtr != '\0')) {
            ALOGE("Picture sizes string \"%s\" contains invalid character.", sizesStr);
            return;
        }
        sizes.push(Size(width, height));

        if (*sizeStartPtr == '\0') {
            return;
        }
        sizeStartPtr++;
    }
}

void QCameraParameters::getSupportedHfrSizes(Vector<Size> &sizes)
{
    const char *hfrSizesStr = get(KEY_QC_SUPPORTED_HFR_SIZES);
    parseSizesList(hfrSizesStr, sizes);
}

int32_t QCameraParameters::setPreviewFpsRange(int minFPS, int maxFPS)
{
    char str[32];
    snprintf(str, sizeof(str), "%d,%d", minFPS, maxFPS);
    ALOGD("%s: Setting preview fps range %s", __func__, str);
    updateParamEntry(KEY_PREVIEW_FPS_RANGE, str);
    cam_fps_range_t fps_range = {minFPS / 1000.0, maxFPS / 1000.0};
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_FPS_RANGE,
                                  sizeof(cam_fps_range_t),
                                  &fps_range);
}

int32_t QCameraParameters::setAutoExposure(const char *autoExp)
{
    if (autoExp != NULL) {
        int32_t value = lookupAttr(AUTO_EXPOSURE_MAP,
                                   sizeof(AUTO_EXPOSURE_MAP)/sizeof(AUTO_EXPOSURE_MAP[0]),
                                   autoExp);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting auto exposure %s", __func__, autoExp);
            updateParamEntry(KEY_QC_AUTO_EXPOSURE, autoExp);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_AEC_ALGO_TYPE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid auto exposure value: %s", (autoExp == NULL) ? "NULL" : autoExp);
    return BAD_VALUE;
}

int32_t QCameraParameters::setEffect(const char *effect)
{
    if (effect != NULL) {
        int32_t value = lookupAttr(EFFECT_MODES_MAP,
                                   sizeof(EFFECT_MODES_MAP)/sizeof(QCameraMap),
                                   effect);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting effect %s", __func__, effect);
            updateParamEntry(KEY_EFFECT, effect);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_EFFECT,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid effect value: %s", (effect == NULL) ? "NULL" : effect);
    return BAD_VALUE;
}

int32_t QCameraParameters::setBrightness(int brightness)
{
    char val[16];
    sprintf(val, "%d", brightness);
    updateParamEntry(KEY_QC_BRIGHTNESS, val);

    int32_t value = brightness;
    ALOGD("%s: Setting brightness %s", __func__, val);
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_BRIGHTNESS,
                                  sizeof(value),
                                  &value);
}

int32_t QCameraParameters::setFocusMode(const char *focusMode)
{
    if (focusMode != NULL) {
        int32_t value = lookupAttr(FOCUS_MODES_MAP,
                                   sizeof(FOCUS_MODES_MAP)/sizeof(QCameraMap),
                                   focusMode);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting focus mode %s", __func__, focusMode);
            mFocusMode = (cam_focus_mode_type)value;
            updateParamEntry(KEY_FOCUS_MODE, focusMode);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_FOCUS_MODE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid focus mode value: %s", (focusMode == NULL) ? "NULL" : focusMode);
    return BAD_VALUE;
}

int32_t QCameraParameters::setSharpness(int sharpness)
{
    char val[16];
    sprintf(val, "%d", sharpness);
    updateParamEntry(KEY_QC_SHARPNESS, val);
    ALOGD("%s: Setting sharpness %s", __func__, val);

    int32_t value = sharpness;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_SHARPNESS,
                                  sizeof(value),
                                  &value);
}

int32_t QCameraParameters::setSkinToneEnhancement(int sceFactor)
{
    char val[16];
    sprintf(val, "%d", sceFactor);
    updateParamEntry(KEY_QC_SCE_FACTOR, val);
    ALOGD("%s: Setting skintone enhancement %s", __func__, val);

    int32_t value = sceFactor;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_SCE_FACTOR,
                                  sizeof(value),
                                  &value);
}

int32_t QCameraParameters::setSaturation(int saturation)
{
    char val[16];
    sprintf(val, "%d", saturation);
    updateParamEntry(KEY_QC_SATURATION, val);
    ALOGD("%s: Setting saturation %s", __func__, val);

    int32_t value = saturation;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_SATURATION,
                                  sizeof(value),
                                  &value);
}

int32_t QCameraParameters::setContrast(int contrast)
{
    char val[16];
    sprintf(val, "%d", contrast);
    updateParamEntry(KEY_QC_CONTRAST, val);
    ALOGD("%s: Setting contrast %s", __func__, val);

    int32_t value = contrast;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_CONTRAST,
                                  sizeof(value),
                                  &value);
}

int32_t QCameraParameters::setSceneDetect(const char *scendDetect)
{
    if (scendDetect != NULL) {
        int32_t value = lookupAttr(TRUE_FALSE_MODES_MAP,
                                   sizeof(TRUE_FALSE_MODES_MAP)/sizeof(QCameraMap),
                                   scendDetect);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting Scene Detect %s", __func__, scendDetect);
            updateParamEntry(KEY_QC_SCENE_DETECT, scendDetect);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_ASD_ENABLE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid Scene Detect value: %s",
          (scendDetect == NULL) ? "NULL" : scendDetect);
    return BAD_VALUE;
}

int32_t QCameraParameters::setZoom(int zoom_level)
{
    char val[16];
    sprintf(val, "%d", zoom_level);
    updateParamEntry(KEY_ZOOM, val);

    int32_t value = m_pCapability->zoom_ratio_tbl[zoom_level];
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_ZOOM,
                                  sizeof(value),
                                  &value);
}

int32_t  QCameraParameters::setISOValue(const char *isoValue)
{
    if (isoValue != NULL) {
        int32_t value = lookupAttr(ISO_MODES_MAP,
                                   sizeof(ISO_MODES_MAP)/sizeof(QCameraMap),
                                   isoValue);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting ISO value %s", __func__, isoValue);
            updateParamEntry(KEY_QC_ISO_MODE, isoValue);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_ISO,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid Scene Detect value: %s",
          (isoValue == NULL) ? "NULL" : isoValue);
    return BAD_VALUE;
}

int32_t QCameraParameters::setFlash(const char *flashStr)
{
    if (flashStr != NULL) {
        int32_t value = lookupAttr(FLASH_MODES_MAP,
                                   sizeof(FLASH_MODES_MAP)/sizeof(QCameraMap),
                                   flashStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting Flash value %s", __func__, flashStr);
            updateParamEntry(KEY_FLASH_MODE, flashStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_LED_MODE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid flash value: %s", (flashStr == NULL) ? "NULL" : flashStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setAecLock(const char *aecLockStr)
{
    if (aecLockStr != NULL) {
        int32_t value = lookupAttr(TRUE_FALSE_MODES_MAP,
                                   sizeof(TRUE_FALSE_MODES_MAP)/sizeof(QCameraMap),
                                   aecLockStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting AECLock value %s", __func__, aecLockStr);
            updateParamEntry(KEY_AUTO_EXPOSURE_LOCK, aecLockStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_AEC_LOCK,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid AECLock value: %s", (aecLockStr == NULL) ? "NULL" : aecLockStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setAwbLock(const char *awbLockStr)
{
    if (awbLockStr != NULL) {
        int32_t value = lookupAttr(TRUE_FALSE_MODES_MAP,
                                   sizeof(TRUE_FALSE_MODES_MAP)/sizeof(QCameraMap),
                                   awbLockStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting AWBLock value %s", __func__, awbLockStr);
            updateParamEntry(KEY_AUTO_WHITEBALANCE_LOCK, awbLockStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_AEC_LOCK,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid AWBLock value: %s", (awbLockStr == NULL) ? "NULL" : awbLockStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setMCEValue(const char *mceStr)
{
    if (mceStr != NULL) {
        int32_t value = lookupAttr(ENABLE_DISABLE_MODES_MAP,
                                   sizeof(ENABLE_DISABLE_MODES_MAP)/sizeof(QCameraMap),
                                   mceStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting AWBLock value %s", __func__, mceStr);
            updateParamEntry(KEY_QC_MEMORY_COLOR_ENHANCEMENT, mceStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_MCE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid MCE value: %s", (mceStr == NULL) ? "NULL" : mceStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setHighFrameRate(const char *hfrStr)
{
    if (hfrStr != NULL) {
        int32_t value = lookupAttr(HFR_MODES_MAP,
                                   sizeof(HFR_MODES_MAP)/sizeof(QCameraMap),
                                   hfrStr);
        if (value != NAME_NOT_FOUND) {
            // HFR value changed, need to restart preview
            m_bNeedRestart = true;
            // Set HFR value
            ALOGD("%s: Setting HFR value %s", __func__, hfrStr);
            updateParamEntry(KEY_QC_VIDEO_HIGH_FRAME_RATE, hfrStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_HFR,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid HFR value: %s", (hfrStr == NULL) ? "NULL" : hfrStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setLensShadeValue(const char *lensShadeStr)
{
    if (lensShadeStr != NULL) {
        int32_t value = lookupAttr(ENABLE_DISABLE_MODES_MAP,
                                   sizeof(ENABLE_DISABLE_MODES_MAP)/sizeof(QCameraMap),
                                   lensShadeStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting LensShade value %s", __func__, lensShadeStr);
            updateParamEntry(KEY_QC_LENSSHADE, lensShadeStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_ROLLOFF,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid LensShade value: %s",
          (lensShadeStr == NULL) ? "NULL" : lensShadeStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setExposureCompensation(int expComp)
{
    char val[16];
    sprintf(val, "%d", expComp);
    updateParamEntry(KEY_EXPOSURE_COMPENSATION, val);

    // Don't need to pass step as part of setParameter because
    // camera daemon is already aware of it.
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_EXPOSURE_COMPENSATION,
                                  sizeof(expComp),
                                  &expComp);
}

int32_t QCameraParameters::setWhiteBalance(const char *wbStr)
{
    if (wbStr != NULL) {
        int32_t value = lookupAttr(WHITE_BALANCE_MODES_MAP,
                                   sizeof(WHITE_BALANCE_MODES_MAP)/sizeof(QCameraMap),
                                   wbStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting WhiteBalance value %s", __func__, wbStr);
            updateParamEntry(KEY_WHITE_BALANCE, wbStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_WHITE_BALANCE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid WhiteBalance value: %s", (wbStr == NULL) ? "NULL" : wbStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setAntibanding(const char *antiBandingStr)
{
    if (antiBandingStr != NULL) {
        int32_t value = lookupAttr(ANTIBANDING_MODES_MAP,
                                   sizeof(ANTIBANDING_MODES_MAP)/sizeof(QCameraMap),
                                   antiBandingStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting AntiBanding value %s", __func__, antiBandingStr);
            updateParamEntry(KEY_ANTIBANDING, antiBandingStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_ANTIBANDING,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("Invalid AntiBanding value: %s",
          (antiBandingStr == NULL) ? "NULL" : antiBandingStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setFocusAreas(const char *focusAreasStr)
{
    if (m_pCapability->max_num_focus_areas == 0 ||
        focusAreasStr == NULL) {
        ALOGI("%s: Parameter string is null", __func__);
        return NO_ERROR;
    }

    cam_rect_t *areas = new cam_rect_t[m_pCapability->max_num_focus_areas];
    int num_areas_found = 0;
    if (parseCameraAreaString(focusAreasStr,
                              m_pCapability->max_num_focus_areas,
                              areas,
                              num_areas_found) != NO_ERROR) {
        ALOGE("%s: Failed to parse the string: %s", __func__, focusAreasStr);
        delete areas;
        return BAD_VALUE;
    }

    if (validateCameraAreas(areas, num_areas_found) == false) {
        ALOGE("%s: invalid areas specified : %s", __func__, focusAreasStr);
        delete areas;
        return BAD_VALUE;
    }

    updateParamEntry(KEY_FOCUS_AREAS, focusAreasStr);

    int previewWidth, previewHeight;
    getPreviewSize(&previewWidth, &previewHeight);
    cam_roi_info_t af_roi_value;
    memset(&af_roi_value, 0, sizeof(cam_roi_info_t));
    af_roi_value.num_roi = num_areas_found;
    for (int i = 0; i < num_areas_found; i++) {
        ALOGD("%s: FocusArea[%d] = (%d, %d, %d, %d)",
              __func__, i, (areas[i].top), (areas[i].left),
              (areas[i].width), (areas[i].height));

        //transform the coords from (-1000, 1000) to (0, previewWidth or previewHeight)
        af_roi_value.roi[i].left = (int32_t)((areas[i].top + 1000.0f) * (previewWidth / 2000.0f));
        af_roi_value.roi[i].top = (int32_t)((areas[i].left + 1000.0f) * (previewHeight / 2000.0f));
        af_roi_value.roi[i].width = (int32_t)(areas[i].width * previewWidth / 2000.0f);
        af_roi_value.roi[i].height = (int32_t)(areas[i].height * previewHeight / 2000.0f);
    }
    delete areas;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_AF_ROI,
                                  sizeof(af_roi_value),
                                  &af_roi_value);
}

int32_t QCameraParameters::setMeteringAreas(const char *meteringAreasStr)
{
    if (m_pCapability->max_num_metering_areas == 0 ||
        meteringAreasStr == NULL) {
        ALOGI("%s: Parameter string is null", __func__);
        return NO_ERROR;
    }

    cam_rect_t *areas = new cam_rect_t[m_pCapability->max_num_metering_areas];
    int num_areas_found = 0;
    if (parseCameraAreaString(meteringAreasStr,
                              m_pCapability->max_num_metering_areas,
                              areas,
                              num_areas_found) < 0) {
        ALOGE("%s: Failed to parse the string: %s", __func__, meteringAreasStr);
        delete areas;
        return BAD_VALUE;
    }

    if (validateCameraAreas(areas, num_areas_found) == false) {
        ALOGE("%s: invalid areas specified : %s", __func__, meteringAreasStr);
        delete areas;
        return BAD_VALUE;
    }

    updateParamEntry(KEY_METERING_AREAS, meteringAreasStr);

    cam_set_aec_roi_t aec_roi_value;
    int previewWidth, previewHeight;
    getPreviewSize(&previewWidth, &previewHeight);

    memset(&aec_roi_value, 0, sizeof(cam_set_aec_roi_t));
    if (num_areas_found > 0) {
        aec_roi_value.aec_roi_enable = CAM_AEC_ROI_ON;
        aec_roi_value.aec_roi_type = CAM_AEC_ROI_BY_COORDINATE;

        for (int i = 0; i < num_areas_found; i++) {
            ALOGD("%s: MeteringArea[%d] = (%d, %d, %d, %d)",
                  __func__, i, (areas[i].top), (areas[i].left),
                  (areas[i].width), (areas[i].height));

            //transform the coords from (-1000, 1000) to (0, previewWidth or previewHeight)
            aec_roi_value.cam_aec_roi_position.coordinate[i].x =
                (uint32_t)(((areas[i].left + areas[i].width / 2) + 1000.0f) * previewWidth / 2000.0f) ;
            aec_roi_value.cam_aec_roi_position.coordinate[i].y =
                (uint32_t)(((areas[i].top + areas[i].height / 2) + 1000.0f) * previewHeight / 2000.0f) ;
        }
    } else {
        aec_roi_value.aec_roi_enable = CAM_AEC_ROI_OFF;
    }
    delete areas;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_AEC_ROI,
                                  sizeof(aec_roi_value),
                                  &aec_roi_value);
}

int32_t QCameraParameters::setSceneMode(const char *sceneModeStr)
{
    if (sceneModeStr != NULL) {
        int32_t value = lookupAttr(SCENE_MODES_MAP,
                                   sizeof(SCENE_MODES_MAP)/sizeof(QCameraMap),
                                   sceneModeStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting SceneMode %s", __func__, sceneModeStr);
            updateParamEntry(KEY_SCENE_MODE, sceneModeStr);
            int32_t rc = AddSetParmEntryToBatch(m_pParamBuf,
                                                CAM_INTF_PARM_FOCUS_ALGO_TYPE,
                                                sizeof(value),
                                                &value);
            return rc;
        }
    }
    ALOGE("%s: Invalid Secene Mode: %s",
          __func__, (sceneModeStr == NULL) ? "NULL" : sceneModeStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setSelectableZoneAf(const char *selZoneAFStr)
{
    if (selZoneAFStr != NULL) {
        int32_t value = lookupAttr(FOCUS_ALGO_MAP,
                                   sizeof(FOCUS_ALGO_MAP)/sizeof(QCameraMap),
                                   selZoneAFStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting Selectable Zone AF value %s", __func__, selZoneAFStr);
            updateParamEntry(KEY_QC_SELECTABLE_ZONE_AF, selZoneAFStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_FOCUS_ALGO_TYPE,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("%s: Invalid selectable zone af value: %s",
          __func__, (selZoneAFStr == NULL) ? "NULL" : selZoneAFStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setAEBracket(const char *aecBracketStr)
{
    cam_exp_bracketing_t expBracket;
    memset(&expBracket, 0, sizeof(expBracket));

    if(isZSLMode()) {
        ALOGE("%s: In ZSL mode, reset AEBBracket to HDR_OFF mode", __func__);
        expBracket.mode = CAM_HDR_BRACKETING_OFF;
    } else {
        if (aecBracketStr != NULL) {
            int value = lookupAttr(HDR_BRACKETING_MODES_MAP,
                                   sizeof(HDR_BRACKETING_MODES_MAP)/sizeof(QCameraMap),
                                   aecBracketStr);
            switch (value) {
            case CAM_HDR_MODE:
                {
                    ALOGD("%s, mHdrMode = HDR", __func__);
                    expBracket.mode = CAM_HDR_MODE;
                }
                break;
            case CAM_EXP_BRACKETING_MODE:
                {
                    ALOGD("%s, mHdrMode = EXP_BRACKETING_MODE", __func__);
                    const char *str_val = get(KEY_QC_CAPTURE_BURST_EXPOSURE);
                    if ((str_val != NULL) && (strlen(str_val)>0)) {
                        ALOGI("%s: %s is %s", __func__, KEY_QC_CAPTURE_BURST_EXPOSURE, str_val);
                        expBracket.mode = CAM_EXP_BRACKETING_MODE;
                        strlcpy(expBracket.values, str_val, MAX_EXP_BRACKETING_LENGTH);
                        ALOGI("%s: setting Exposure Bracketing value of %s",
                              __func__, expBracket.values);
                    }
                    else {
                        /* Apps not set capture-burst-exposures, error case fall into bracketing off mode */
                        ALOGI("%s: capture-burst-exposures not set, back to HDR OFF mode", __func__);
                        expBracket.mode = CAM_HDR_BRACKETING_OFF;
                    }
                }
                break;
            case CAM_HDR_BRACKETING_OFF:
            default:
                {
                    ALOGD("%s, mHdrMode = HDR_BRACKETING_OFF", __func__);
                    expBracket.mode = CAM_HDR_BRACKETING_OFF;
                }
                break;
            }
        }
    }

    /* save the value*/
    updateParamEntry(KEY_QC_AE_BRACKET_HDR, aecBracketStr);
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_HDR,
                                  sizeof(expBracket),
                                  &expBracket);
}

int32_t QCameraParameters::setRedeyeReduction(const char *redeyeStr)
{
    if (redeyeStr != NULL) {
        int32_t value = lookupAttr(ENABLE_DISABLE_MODES_MAP,
                                   sizeof(ENABLE_DISABLE_MODES_MAP)/sizeof(QCameraMap),
                                   redeyeStr);
        if (value != NAME_NOT_FOUND) {
            ALOGD("%s: Setting RedEye Reduce value %s", __func__, redeyeStr);
            updateParamEntry(KEY_QC_REDEYE_REDUCTION, redeyeStr);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_REDEYE_REDUCTION,
                                          sizeof(value),
                                          &value);
        }
    }
    ALOGE("%s: Invalid RedEye Reduce value: %s",
          __func__, (redeyeStr == NULL) ? "NULL" : redeyeStr);
    return BAD_VALUE;
}

int32_t QCameraParameters::setWaveletDenoise(const char *wnrStr)
{
    if (wnrStr != NULL) {
        int value = lookupAttr(DENOISE_ON_OFF_MODES_MAP,
                               sizeof(DENOISE_ON_OFF_MODES_MAP)/sizeof(QCameraMap),
                               wnrStr);
        if (value != NAME_NOT_FOUND) {
            updateParamEntry(KEY_QC_DENOISE, wnrStr);

            cam_denoise_param_t temp;
            memset(&temp, 0, sizeof(temp));
            temp.denoise_enable = value;
            m_bWNROn = (value != 0);
            if (m_bWNROn) {
                char prop[PROPERTY_VALUE_MAX];
                memset(prop, 0, sizeof(prop));
                property_get("persist.denoise.process.plates", prop, "0");
                int processPlate = atoi(prop);
                switch(processPlate) {
                case 0:
                    temp.process_plates = CAM_WAVELET_DENOISE_YCBCR_PLANE;
                    break;
                case 1:
                    temp.process_plates = CAM_WAVELET_DENOISE_CBCR_ONLY;
                    break;
                case 2:
                    temp.process_plates = CAM_WAVELET_DENOISE_STREAMLINE_YCBCR;
                    break;
                case 3:
                    temp.process_plates = CAM_WAVELET_DENOISE_STREAMLINED_CBCR;
                    break;
                default:
                    temp.process_plates = CAM_WAVELET_DENOISE_STREAMLINE_YCBCR;
                    break;
                }
            }
            ALOGI("%s: Denoise enable=%d, plates=%d",
                  __func__, temp.denoise_enable, temp.process_plates);
            return AddSetParmEntryToBatch(m_pParamBuf,
                                          CAM_INTF_PARM_WAVELET_DENOISE,
                                          sizeof(temp),
                                          &temp);
        }
    }
    ALOGE("%s: Invalid Denoise value: %s", __func__, (wnrStr == NULL) ? "NULL" : wnrStr);
    return BAD_VALUE;
}

void QCameraParameters::setPreviewFrameRateMode(const char *mode)
{
    set(KEY_QC_PREVIEW_FRAME_RATE_MODE, mode);
}

const char *QCameraParameters::getPreviewFrameRateMode() const
{
    return get(KEY_QC_PREVIEW_FRAME_RATE_MODE);
}

void QCameraParameters::setTouchIndexAec(int x, int y)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", x, y);
    set(KEY_QC_TOUCH_INDEX_AEC, str);
}

void QCameraParameters::getTouchIndexAec(int *x, int *y)
{
    *x = -1;
    *y = -1;

    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_QC_TOUCH_INDEX_AEC);
    if (p == 0)
        return;

    int tempX, tempY;
    if (parse_pair(p, &tempX, &tempY, 'x') == 0) {
        *x = tempX;
        *y = tempY;
    }
}

void QCameraParameters::setTouchIndexAf(int x, int y)
{
    char str[32];
    snprintf(str, sizeof(str), "%dx%d", x, y);
    set(KEY_QC_TOUCH_INDEX_AF, str);
}

void QCameraParameters::getTouchIndexAf(int *x, int *y)
{
    *x = -1;
    *y = -1;

    // Get the current string, if it doesn't exist, leave the -1x-1
    const char *p = get(KEY_QC_TOUCH_INDEX_AF);
    if (p == 0)
        return;

    int tempX, tempY;
    if (parse_pair(p, &tempX, &tempY, 'x') == 0) {
        *x = tempX;
        *y = tempY;
	}
}

int32_t QCameraParameters::getStreamFormat(cam_stream_type_t streamType,
                                            cam_format_t &format)
{
    int32_t ret = NO_ERROR;

    format = CAM_FORMAT_MAX;
    switch (streamType) {
    case CAM_STREAM_TYPE_PREVIEW:
    case CAM_STREAM_TYPE_POSTVIEW:
        format = mPreviewFormat;
        break;
    case CAM_STREAM_TYPE_SNAPSHOT:
    case CAM_STREAM_TYPE_OFFLINE_PROC:
        format = CAM_FORMAT_YUV_420_NV21;
        break;
    case CAM_STREAM_TYPE_VIDEO:
        format = CAM_FORMAT_YUV_420_NV12;
        break;
    case CAM_STREAM_TYPE_RAW:
        if (mPictureFormat >= CAM_FORMAT_YUV_RAW_8BIT) {
            format = (cam_format_t)mPictureFormat;
        } else {
            ALOGE("%s: invalid raw picture format: %d", __func__, mPictureFormat);
            ret = BAD_VALUE;
        }
        break;
    case CAM_STREAM_TYPE_METADATA:
    case CAM_STREAM_TYPE_DEFAULT:
    default:
        break;
    }

    return ret;
}

int32_t QCameraParameters::getStreamDimension(cam_stream_type_t streamType,
                                               cam_dimension_t &dim)
{
    int32_t ret = NO_ERROR;

    memset(&dim, 0, sizeof(cam_dimension_t));

    switch (streamType) {
    case CAM_STREAM_TYPE_PREVIEW:
        getPreviewSize(&dim.width, &dim.height);
        break;
    case CAM_STREAM_TYPE_POSTVIEW:
        getPreviewSize(&dim.width, &dim.height);
        break;
    case CAM_STREAM_TYPE_SNAPSHOT:
        getPictureSize(&dim.width, &dim.height);
        break;
    case CAM_STREAM_TYPE_VIDEO:
        getVideoSize(&dim.width, &dim.height);
        break;
    case CAM_STREAM_TYPE_RAW:
        dim = m_pCapability->raw_dim;
        break;
    case CAM_STREAM_TYPE_METADATA:
        dim.width = sizeof(cam_metadata_info_t);
        dim.height = 1;
        break;
    case CAM_STREAM_TYPE_OFFLINE_PROC:
        getPictureSize(&dim.width, &dim.height);
        break;
    case CAM_STREAM_TYPE_DEFAULT:
    default:
        ALOGE("%s: no dimension for unsupported stream type %d",
              __func__, streamType);
        ret = BAD_VALUE;
        break;
    }
    return ret;
}

int QCameraParameters::getPreviewHalPixelFormat() const
{
    int32_t halPixelFormat;

    switch (mPreviewFormat) {
    case CAM_FORMAT_YUV_420_NV12:
        halPixelFormat = HAL_PIXEL_FORMAT_YCbCr_420_SP;
        break;
    case CAM_FORMAT_YUV_420_NV21:
        halPixelFormat = HAL_PIXEL_FORMAT_YCrCb_420_SP;
        break;
    case CAM_FORMAT_YUV_420_NV21_ADRENO:
        halPixelFormat = HAL_PIXEL_FORMAT_YCrCb_420_SP_ADRENO;
        break;
    case CAM_FORMAT_YUV_420_YV12:
        halPixelFormat = HAL_PIXEL_FORMAT_YV12;
        break;
    case CAM_FORMAT_YUV_422_NV16:
    case CAM_FORMAT_YUV_422_NV61:
    default:
        halPixelFormat = HAL_PIXEL_FORMAT_YCrCb_420_SP;
        break;
    }
    ALOGE("%s: format %d\n", __func__, halPixelFormat);
    return halPixelFormat;
}

void QCameraParameters::getThumbnailSize(int *width, int *height) const
{
    *width = getInt(KEY_JPEG_THUMBNAIL_WIDTH);
    *height = getInt(KEY_JPEG_THUMBNAIL_HEIGHT);
}

int QCameraParameters::getZSLBurstInterval()
{
    int interval = getInt(KEY_QC_ZSL_BURST_INTERVAL);
    if (interval < 0) {
        interval = 1;
    }
    return interval;
}

int QCameraParameters::getZSLQueueDepth()
{
    int qdepth = getInt(KEY_QC_ZSL_QUEUE_DEPTH);
    if (qdepth < 0) {
        qdepth = 2;
    }
    return qdepth;
}

int QCameraParameters::getZSLBackLookCount()
{
    int look_back = getInt(KEY_QC_ZSL_BURST_LOOKBACK);
    if (look_back < 0) {
        look_back = 2;
    }
    return look_back;
}

int QCameraParameters::setRecordingHintValue(int32_t value)
{
    ALOGD("%s: VideoHint = %d", __func__, value);
    m_bRecordingHint = (value > 0)? true : false;
    return AddSetParmEntryToBatch(m_pParamBuf,
                                  CAM_INTF_PARM_RECORDING_HINT,
                                  sizeof(value),
                                  &value);
}

uint8_t QCameraParameters::getNumOfSnapshots()
{
    int numOfSnapshot = getInt(KEY_QC_NUM_SNAPSHOT_PER_SHUTTER);
    if (numOfSnapshot < 0) {
        numOfSnapshot = 1; // set to default value
    }
    return (uint8_t)numOfSnapshot;
}

int QCameraParameters::getJpegQuality()
{
    int quality = getInt(KEY_JPEG_QUALITY);
    if (quality < 0) {
        quality = 85; // set to default quality value
    }
    return quality;
}

int QCameraParameters::getJpegRotation() {
    int rotation = getInt(KEY_ROTATION);
    if (rotation < 0) {
        rotation = 0;
    }
    return rotation;
}

int QCameraParameters::parseGPSCoordinate(const char *coord_str, rat_t* coord)
{
    if(coord == NULL) {
        ALOGE("%s: error, invalid argument coord == NULL", __func__);
        return BAD_VALUE;
    }
    float degF = atof(coord_str);
    if (degF < 0) {
        degF = -degF;
    }
    float minF = (degF - (int) degF) * 60;
    float secF = (minF - (int) minF) * 60;

    getRational(&coord[0], (int)degF, 1);
    getRational(&coord[1], (int)minF, 1);
    getRational(&coord[2], (int)(secF * 10000), 10000);
    return NO_ERROR;
}

int32_t QCameraParameters::getExifDateTime(char *dateTime, uint32_t &count)
{
    //get time and date from system
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime (&rawtime);
    //Write datetime according to EXIF Spec
    //"YYYY:MM:DD HH:MM:SS" (20 chars including \0)
    snprintf(dateTime, 20, "%04d:%02d:%02d %02d:%02d:%02d",
             timeinfo->tm_year + 1900, timeinfo->tm_mon + 1,
             timeinfo->tm_mday, timeinfo->tm_hour,
             timeinfo->tm_min, timeinfo->tm_sec);
    count = 20;

    return NO_ERROR;
}

int32_t QCameraParameters::getRational(rat_t *rat, int num, int denom)
{
    if (NULL == rat) {
        ALOGE("%s: NULL rat input", __func__);
        return BAD_VALUE;
    }
    rat->num = num;
    rat->denom = denom;
    return NO_ERROR;
}

int32_t QCameraParameters::getExifFocalLength(rat_t *focalLength)
{
    int focalLengthValue =
        (int)(getFloat(QCameraParameters::KEY_FOCAL_LENGTH) * FOCAL_LENGTH_DECIMAL_PRECISION);
    return getRational(focalLength, focalLengthValue, FOCAL_LENGTH_DECIMAL_PRECISION);
}

uint16_t QCameraParameters::getExifIsoSpeed()
{
    uint16_t isoSpeed = 0;
    const char *iso_str = get(QCameraParameters::KEY_QC_ISO_MODE);
    int iso_index = lookupAttr(ISO_MODES_MAP,
        sizeof(ISO_MODES_MAP)/sizeof(ISO_MODES_MAP[0]), iso_str);
    switch (iso_index) {
    case CAM_ISO_MODE_AUTO:
        isoSpeed = 0;
        break;
    case CAM_ISO_MODE_DEBLUR:
        isoSpeed = 1;
        break;
    case CAM_ISO_MODE_100:
        isoSpeed = 100;
        break;
    case CAM_ISO_MODE_200:
        isoSpeed = 200;
        break;
    case CAM_ISO_MODE_400:
        isoSpeed = 400;
        break;
    case CAM_ISO_MODE_800:
        isoSpeed = 800;
        break;
    case CAM_ISO_MODE_1600:
        isoSpeed = 1600;
        break;
    }
    return isoSpeed;
}

int32_t QCameraParameters::getExifGpsProcessingMethod(char *gpsProcessingMethod,
                                                      uint32_t &count)
{
    const char *str = get(KEY_GPS_PROCESSING_METHOD);
    if(str != NULL) {
        memcpy(gpsProcessingMethod, ExifAsciiPrefix, EXIF_ASCII_PREFIX_SIZE);
        count = EXIF_ASCII_PREFIX_SIZE;
        strncpy(gpsProcessingMethod + EXIF_ASCII_PREFIX_SIZE, str, strlen(str));
        count += strlen(str);
        gpsProcessingMethod[count++] = '\0'; // increase 1 for the last NULL char
        return NO_ERROR;
    } else {
        return BAD_VALUE;
    }
}

int32_t QCameraParameters::getExifLatitude(rat_t *latitude,
                                           char *latRef)
{
    const char *str = get(KEY_GPS_LATITUDE);
    if(str != NULL) {
        parseGPSCoordinate(str, latitude);

        //set Latitude Ref
        float latitudeValue = getFloat(KEY_GPS_LATITUDE);
        if(latitudeValue < 0.0f) {
            latRef[0] = 'S';
        } else {
            latRef[0] = 'N';
        }
        latRef[1] = '\0';
        return NO_ERROR;
    }else{
        return BAD_VALUE;
    }
}

int32_t QCameraParameters::getExifLongitude(rat_t *longitude,
                                            char *lonRef)
{
    const char *str = get(KEY_GPS_LONGITUDE);
    if(str != NULL) {
        parseGPSCoordinate(str, longitude);

        //set Longitude Ref
        float longitudeValue = getFloat(KEY_GPS_LONGITUDE);
        if(longitudeValue < 0.0f) {
            lonRef[0] = 'W';
        } else {
            lonRef[0] = 'E';
        }
        lonRef[1] = '\0';
        return NO_ERROR;
    }else{
        return BAD_VALUE;
    }
}

int32_t QCameraParameters::getExifAltitude(rat_t *altitude,
                                           char *altRef)
{
    const char *str = get(KEY_GPS_ALTITUDE);
    if(str != NULL) {
        double value = atof(str);
        *altRef = 0;
        if(value < 0){
            *altRef = 1;
            value = -value;
        }
        return getRational(altitude, value*1000, 1000);
    }else{
        return BAD_VALUE;
    }
}

int32_t QCameraParameters::getExifGpsDateTimeStamp(char *gpsDateStamp,
                                                   uint32_t bufLen,
                                                   rat_t *gpsTimeStamp)
{
    const char *str = get(KEY_GPS_TIMESTAMP);
    if(str != NULL) {
        time_t unixTime = (time_t)atol(str);
        struct tm *UTCTimestamp = gmtime(&unixTime);

        strftime(gpsDateStamp, bufLen, "%Y:%m:%d", UTCTimestamp);

        getRational(&gpsTimeStamp[0], UTCTimestamp->tm_hour, 1);
        getRational(&gpsTimeStamp[1], UTCTimestamp->tm_min, 1);
        getRational(&gpsTimeStamp[2], UTCTimestamp->tm_sec, 1);

        return NO_ERROR;
    } else {
        return BAD_VALUE;
    }
}

int32_t QCameraParameters::updateFocusDistances(cam_focus_distances_info_t *focusDistances)
{
    String8 str;
    char buffer[32] = {0};
    //set all distances to infinity if focus mode is infinity
    if(mFocusMode == CAM_FOCUS_MODE_INFINITY) {
        str.append("Infinity,Infinity,Infinity");
    } else {
        snprintf(buffer, sizeof(buffer), "%f", focusDistances->focus_distance[0]);
        str.append(buffer);
        snprintf(buffer, sizeof(buffer), ",%f", focusDistances->focus_distance[1]);
        str.append(buffer);
        snprintf(buffer, sizeof(buffer), ",%f", focusDistances->focus_distance[2]);
        str.append(buffer);
    }
    ALOGD("%s: setting KEY_FOCUS_DISTANCES as %s", __FUNCTION__, str.string());
    set(QCameraParameters::KEY_FOCUS_DISTANCES, str.string());
    return NO_ERROR;
}

int32_t QCameraParameters::setHistogram(bool enabled)
{
    if(m_bHistogramEnabled == enabled) {
        ALOGD("%s: histogram flag not changed, no ops here", __func__);
        return NO_ERROR;
    }

    // set parm for histogram
    if(initBatchUpdate(m_pParamBuf) < 0 ) {
        ALOGE("%s:Failed to initialize group update table", __func__);
        return BAD_TYPE;
    }

    int8_t value = enabled;
    int32_t rc = NO_ERROR;
    rc = AddSetParmEntryToBatch(m_pParamBuf,
                                CAM_INTF_PARM_HISTOGRAM,
                                sizeof(value),
                                &value);
    if (rc != NO_ERROR) {
        ALOGE("%s:Failed to update table", __func__);
        return rc;
    }

    rc = commitSetBatch();
    if (rc != NO_ERROR) {
        ALOGE("%s:Failed to set histogram", __func__);
        return rc;
    }

    m_bHistogramEnabled = enabled;

    ALOGD(" Histogram -> %s", m_bHistogramEnabled ? "Enabled" : "Disabled");

    return rc;
}

int32_t QCameraParameters::setFaceDetection(bool enabled)
{
    if(m_bFaceDetectionEnabled == enabled) {
        ALOGD("%s: face detection flag not changed, no ops here", __func__);
        return NO_ERROR;
    }

    // set parm for face detection
    int requested_faces = getInt(QCameraParameters::KEY_QC_MAX_NUM_REQUESTED_FACES);
    cam_fd_set_parm_t fd_set_parm;
    memset(&fd_set_parm, 0, sizeof(cam_fd_set_parm_t));
    fd_set_parm.fd_mode = enabled;
    fd_set_parm.num_fd = requested_faces;

    if(initBatchUpdate(m_pParamBuf) < 0 ) {
        ALOGE("%s:Failed to initialize group update table", __func__);
        return BAD_TYPE;
    }
    int32_t rc = NO_ERROR;

    rc = AddSetParmEntryToBatch(m_pParamBuf,
                                CAM_INTF_PARM_FD,
                                sizeof(fd_set_parm),
                                &fd_set_parm);
    if (rc != NO_ERROR) {
        ALOGE("%s:Failed to update table", __func__);
        return rc;
    }

    rc = commitSetBatch();
    if (rc != NO_ERROR) {
        ALOGE("%s:Failed to set face detection parm", __func__);
        return rc;
    }

    m_bFaceDetectionEnabled = enabled;
    ALOGD(" FaceDetection -> %s", m_bFaceDetectionEnabled ? "Enabled" : "Disabled");

    return rc;
}

int32_t QCameraParameters::setBundleInfo(cam_bundle_config_t &bundle_info)
{
    int32_t rc = NO_ERROR;

    if(initBatchUpdate(m_pParamBuf) < 0 ) {
        ALOGE("%s:Failed to initialize group update table", __func__);
        return BAD_TYPE;
    }

    rc = AddSetParmEntryToBatch(m_pParamBuf,
                                CAM_INTF_PARM_SET_BUNDLE,
                                sizeof(cam_bundle_config_t),
                                &bundle_info);
    if (rc != NO_ERROR) {
        ALOGE("%s:Failed to update table", __func__);
        return rc;
    }

    rc = commitSetBatch();
    if (rc != NO_ERROR) {
        ALOGE("%s:Failed to set bundle info parm", __func__);
        return rc;
    }

    return rc;
}

// Parse string like "(1, 2, 3, 4, ..., N)"
// num is pointer to an allocated array of size N
int32_t QCameraParameters::parseNDimVector(const char *str, int *num, int N, char delim = ',')
{
    char *start, *end;
    if (num == NULL) {
        ALOGE("%s: Invalid output array (num == NULL)", __func__);
        return BAD_VALUE;
    }

    //check if string starts and ends with parantheses
    if(str[0] != '(' || str[strlen(str)-1] != ')') {
        ALOGE("%s: Invalid format of string %s, valid format is (n1, n2, n3, n4 ...)",
              __func__, str);
        return BAD_VALUE;
    }
    start = (char*) str;
    start++;
    for(int i=0; i<N; i++) {
        *(num+i) = (int) strtol(start, &end, 10);
        if(*end != delim && i < N-1) {
            ALOGE("%s: Cannot find delimeter '%c' in string \"%s\". end = %c",
                  __func__, delim, str, *end);
            return -1;
        }
        start = end+1;
    }
    return NO_ERROR;
}

// parse string like "(1, 2, 3, 4, 5),(1, 2, 3, 4, 5),..."
int32_t QCameraParameters::parseCameraAreaString(const char *str,
                                                 int max_num_areas,
                                                 cam_rect_t *pAreas,
                                                 int& num_areas_found)
{
    char area_str[32];
    const char *start, *end, *p;
    start = str; end = NULL;
    int values[4], index=0;
    num_areas_found = 0;

    while(start != NULL) {
       if(*start != '(') {
            ALOGE("%s: error: Ill formatted area string: %s", __func__, str);
            return BAD_VALUE;
       }
       end = strchr(start, ')');
       if(end == NULL) {
            ALOGE("%s: error: Ill formatted area string: %s", __func__, str);
            return BAD_VALUE;
       }
       int i;
       for (i=0,p=start; p<=end; p++, i++) {
           area_str[i] = *p;
       }
       area_str[i] = '\0';
       if(parseNDimVector(area_str, values, 5) < 0){
            ALOGE("%s: error: Failed to parse the area string: %s", __func__, area_str);
            return BAD_VALUE;
       }
       // no more areas than max_num_areas are accepted.
       if(index >= max_num_areas) {
            ALOGE("%s: error: too many areas specified %s", __func__, str);
            return BAD_VALUE;
       }
       pAreas[index].left = values[0];
       pAreas[index].top = values[1];
       pAreas[index].width = values[2] - values[0];
       pAreas[index].height = values[3] - values[1];

       index++;
       start = strchr(end, '('); // serach for next '('
    }
    num_areas_found = index;
    return 0;
}

bool QCameraParameters::validateCameraAreas(cam_rect_t *areas, int num_areas)
{
    for(int i = 0; i < num_areas; i++) {
        // left should be >= -1000
        if(areas[i].left < -1000) {
            return false;
        }

        // top  should be >= -1000
        if(areas[i].top < -1000) {
            return false;
        }

        // right  should be <= 1000
        if(areas[i].left + areas[i].width > 1000) {
            return false;
        }

        // bottom should be <= 1000
        if(areas[i].top + areas[i].height > 1000) {
            return false;
        }
    }
    return true;
}

int32_t QCameraParameters::initBatchUpdate(parm_buffer_t *p_table)
{
    m_tempMap.clear();

    memset(p_table, 0, sizeof(parm_buffer_t));
    p_table->first_flagged_entry = CAM_INTF_PARM_MAX;
    return NO_ERROR;
}

int32_t QCameraParameters::AddSetParmEntryToBatch(parm_buffer_t *p_table,
                                                  cam_intf_parm_type_t paramType,
                                                  uint32_t paramLength,
                                                  void *paramValue)
{
    int position = paramType;
    int current, next;

    /*************************************************************************
    *                 Code to take care of linking next flags                *
    *************************************************************************/
    current = GET_FIRST_PARAM_ID(p_table);
    if (position == current){
        //DO NOTHING
    } else if (position < current){
        SET_NEXT_PARAM_ID(position, p_table, current);
        SET_FIRST_PARAM_ID(p_table, position);
    } else {
        /* Search for the position in the linked list where we need to slot in*/
        while (position > GET_NEXT_PARAM_ID(current, p_table))
            current = GET_NEXT_PARAM_ID(current, p_table);

        /*If node already exists no need to alter linking*/
        if (position != GET_NEXT_PARAM_ID(current, p_table)) {
            next = GET_NEXT_PARAM_ID(current, p_table);
            SET_NEXT_PARAM_ID(current, p_table, position);
            SET_NEXT_PARAM_ID(position, p_table, next);
        }
    }

    /*************************************************************************
    *                   Copy contents into entry                             *
    *************************************************************************/

    if (paramLength > sizeof(parm_type_t)) {
        ALOGE("%s:Size of input larger than max entry size",__func__);
        return BAD_VALUE;
    }
    memcpy(POINTER_OF(paramType,p_table), paramValue, paramLength);
    return NO_ERROR;
}

int32_t QCameraParameters::AddGetParmEntryToBatch(parm_buffer_t *p_table,
                                                  cam_intf_parm_type_t paramType)
{
    int position = paramType;
    int current, next;

    /*************************************************************************
    *                 Code to take care of linking next flags                *
    *************************************************************************/
    current = GET_FIRST_PARAM_ID(p_table);
    if (position == current){
        //DO NOTHING
    } else if (position < current){
        SET_NEXT_PARAM_ID(position, p_table, current);
        SET_FIRST_PARAM_ID(p_table, position);
    } else {
        /* Search for the position in the linked list where we need to slot in*/
        while (position > GET_NEXT_PARAM_ID(current, p_table))
            current = GET_NEXT_PARAM_ID(current, p_table);

        /*If node already exists no need to alter linking*/
        if (position != GET_NEXT_PARAM_ID(current, p_table)) {
            next=GET_NEXT_PARAM_ID(current, p_table);
            SET_NEXT_PARAM_ID(current, p_table, position);
            SET_NEXT_PARAM_ID(position, p_table, next);
        }
    }

    return NO_ERROR;
}

int32_t QCameraParameters::commitSetBatch()
{
    int32_t rc = m_pCamOpsTbl->ops->set_parms(m_pCamOpsTbl->camera_handle, m_pParamBuf);
    if (rc == NO_ERROR) {
        // commit change from temp storage into param map
        rc = commitParamChanges();
    }
    return rc;
}

int32_t QCameraParameters::commitGetBatch()
{
    return m_pCamOpsTbl->ops->get_parms(m_pCamOpsTbl->camera_handle, m_pParamBuf);
}

int32_t QCameraParameters::updateParamEntry(const char *key, const char *value)
{
    m_tempMap.replaceValueFor(String8(key), String8(value));
    return NO_ERROR;
}

int32_t QCameraParameters::commitParamChanges()
{
    size_t size = m_tempMap.size();
    for (size_t i = 0; i < size; i++) {
        String8 k, v;
        k = m_tempMap.keyAt(i);
        v = m_tempMap.valueAt(i);
        set(k, v);
    }
    m_tempMap.clear();
    return NO_ERROR;
}

}; // namespace qcamera
