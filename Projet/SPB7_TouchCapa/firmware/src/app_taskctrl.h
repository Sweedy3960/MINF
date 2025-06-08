#ifndef APP_TASKCTRL_H
#define APP_TASKCTRL_H

#include <stdbool.h>

typedef struct {
    bool isActive;
    bool isDirty;
} app_task_ctrl_t;

// Declare task control instances
extern app_task_ctrl_t touchTaskCtrl;
// Add more for other modules:
extern app_task_ctrl_t ledTaskCtrl;
extern app_task_ctrl_t displayTaskCtrl;
// ...

#endif // APP_TASKCTRL_H
