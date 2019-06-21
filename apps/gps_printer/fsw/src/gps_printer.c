#include "cfe.h"
#include "gps_reader_msgids.h"
#include "gps_reader_msgs.h"

CFE_SB_PipeId_t gpsPipe;
CFE_SB_Msg_t gpsMessage;

void GPS_PRINTER_Main(void) {
    uint32 runStatus = CFE_ES_APP_RUN;
    GPS_PRINTER_Init();

    while (CFE_ES_RunLoop(&runStatus) == TRUE) {
        int32 status = CFE_SB_RcvMsg(&gpsMessage, &gpsPipe, CFE_SB_PEND_FOREVER);
        OS_printf("GPS_PRINTER: got a gps message");
    }
}

void GPS_PRINTER_Init(void) {
    CFE_ES_RegisterApp();
    CFE_EVS_Register(NULL, 0, CFE_EVS_BINARY_FILTER);

    CFE_SB_CreatePipe(&gpsPipe, 50, "GPS_PRINTER_PIPE");
    CFE_SB_Subscribe(GPS_READER_GPS_INFO_MSG, &gpsPipe);
}
