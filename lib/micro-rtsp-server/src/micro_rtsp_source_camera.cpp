#include <Arduino.h>

#include "micro_rtsp_source_camera.h"

micro_rtsp_source_camera::micro_rtsp_source_camera()
{
    init_result == ESP_FAIL;
}

micro_rtsp_source_camera::~micro_rtsp_source_camera()
{
    deinitialize();
}

esp_err_t micro_rtsp_source_camera::initialize(camera_config_t *camera_config)
{

    init_result = esp_camera_init(camera_config);
    if (init_result == ESP_OK)
        update_frame();
    else
        log_e("Camera initialization failed: 0x%x", init_result);
}

esp_err_t micro_rtsp_source_camera::deinitialize()
{
    return init_result == ESP_OK ? esp_camera_deinit() : ESP_OK;
}

void micro_rtsp_source_camera::update_frame()
{
    if (fb)
        esp_camera_fb_return(fb);

    fb = esp_camera_fb_get();
}