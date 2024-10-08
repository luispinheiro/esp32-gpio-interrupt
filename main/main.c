#include <stdio.h> // c language input and output libraries

// freeRTOS Libraries
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// ESP32 Libraries
#include "driver/gpio.h"
#include "esp_log.h"

//pin mapping
#define LED1_PIN 21          //GPIO21
#define LED2_PIN 33          //GPIO33
#define LED3_PIN 14          //GPIO14
#define BUTTON1_PIN 2        //GPIO2
#define BUTTON2_PIN 3        //GPIO3

static const char *TAG = "BUTTON TEST: ";

static QueueHandle_t gpio_evt_queue = NULL;

static void IRAM_ATTR gpio_isr_handler(void* arg){
    
}

void buttonTask(void *pvpameters){

    while (true)
    {
            
    }
}

void app_main(void)
{

//initialize LED_PIN_1 and LED_PIN_2 as output
    gpio_reset_pin(LED1_PIN);                          //reset pin and set as GPIO
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);    //set as output
    gpio_reset_pin(LED2_PIN);                          //reset pin and set as GPIO
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);    //set as output   
    gpio_reset_pin(LED3_PIN);                          //reset pin and set as GPIO
    gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT);    //set as output 

    //turn off led1, led2 and led3
    gpio_set_level(LED1_PIN, 0);                            //turn off led1
    gpio_set_level(LED2_PIN, 0);                            //turn off led2
    gpio_set_level(LED3_PIN, 0);                            //turn off led3

    gpio_reset_pin(BUTTON1_PIN);                   //select BUTTON_PIN as GPIO
    gpio_set_direction(BUTTON1_PIN, GPIO_MODE_INPUT);    //set as input
    gpio_pullup_en(BUTTON1_PIN);                         //enable pull-up
    gpio_set_intr_type(BUTTON1_PIN, GPIO_INTR_NEGEDGE);  //interrupt on negative edge

    gpio_evt_queue  = xQueueCreate(1, sizeof(uint32_t));         //create queue to handle gpio event from ISR
    xTaskCreate(buttonTask, "buttonTask", 2048, NULL, 2, NULL);  //create button task

    gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);                  //install interrupt service routine
    gpio_isr_handler_add(BUTTON1_PIN, gpio_isr_handler, (void*) BUTTON1_PIN);  //add ISR handler for button

    while(true){
        //toogle led3
        gpio_set_level(LED3_PIN, 1);                //turn on led3
        vTaskDelay(pdMS_TO_TICKS(500));             //delay 500ms
        gpio_set_level(LED3_PIN, 0);                //turn off led3
        vTaskDelay(pdMS_TO_TICKS(500));             //delay 500ms

    }

}
