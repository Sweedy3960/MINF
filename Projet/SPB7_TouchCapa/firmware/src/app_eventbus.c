//app_eventbus.c
#include "app_eventbus.h"
#include "appDisp.h"

#include "appTouch.h"
#include "appReg.h"
void App_EventBus_Publish(app_event_t evt, uint16_t *data)
{
    switch (evt) {
        case EVT_TOUCH:
            
            App_Display_HandleTouch(data);    //
            App_LED_HandleTouch(data);      // Trigger LED if error ack
            break;

        case EVT_INPUTS:
            //App_Display_HandleInputs(data);    //
            //App_LED_HandleInputs(data);      // Trigger LED if error ack
            //this need to be done
            break;
        
        default:
            break;
    }
}
