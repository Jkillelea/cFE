#include "cfe.h"
#include "gps_reader_msgids.h"
#include "gps_reader_msgs.h"
#include "gps_print_msgs.h"

CFE_SB_PipeId_t gpsPipe;
CFE_SB_MsgPtr_t gpsMessage;

void GPS_PRINTER_Main(void) {
    uint32 runStatus = CFE_ES_APP_RUN;
    GPS_PRINTER_Init();

    while (CFE_ES_RunLoop(&runStatus) == TRUE) {
        int32 status = CFE_SB_RcvMsg(&gpsMessage, gpsPipe, CFE_SB_PEND_FOREVER);
        if (status == CFE_SUCCESS) {
            OS_printf("GPS_PRINTER: got a gps message\n");
            
            CFE_SB_MsgId_t msgId = CFE_SB_GetMsgId(gpsMessage);
            
            switch (msgId) {
            case GPS_READER_GPS_INFO_MSG:
                OS_printf("GPS_PRINTER: GPS_READER_GPS_INFO_MSG Message (0x%x)\n", msgId);
                GpsInfoMsg_t *gpsInfo = gpsMessage;
                print_info(&gpsInfo->gpsInfo);
                break;
            case GPS_READER_GPS_GPGGA_MSG:
                OS_printf("GPS_PRINTER: GPS_READER_GPS_GPGGA_MSG Message (0x%x)\n", msgId);
                GpsGpggaMsg_t *gpsGpgga = gpsMessage;
                print_gpgga(&gpsGpgga->gpsGpgga);
                break;
            case GPS_READER_GPS_GPGSA_MSG:
                OS_printf("GPS_PRINTER: GPS_READER_GPS_GPGSA_MSG Message (0x%x)\n", msgId);
                GpsGpgsaMsg_t *gpsGpgsa = gpsMessage;
                print_gpgsa(&gpsGpgsa->gpsGpgsa);
                break;
            case GPS_READER_GPS_GPRMC_MSG:
                OS_printf("GPS_PRINTER: GPS_READER_GPS_GPRMC_MSG Message (0x%x)\n", msgId);
                GpsGprmcMsg_t *gpsGprmc = gpsMessage;
                print_gprmc(&gpsGprmc->gpsGprmc);
                break;
            case GPS_READER_GPS_GPVTG_MSG:
                OS_printf("GPS_PRINTER: GPS_READER_GPS_GPVTG_MSG Message (0x%x)\n", msgId);
                GpsGpvtgMsg_t *gpsGpvtg = gpsMessage;
                print_gpvtg(&gpsGpvtg->gpsGpvtg);
                break;
            default:
                OS_printf("GPS_PRINTER: Unkown message ID 0x%x\n", msgId);
                break;
            }
        }
    }
}

void GPS_PRINTER_Init(void) {
    CFE_ES_RegisterApp();
    CFE_EVS_Register(NULL, 0, CFE_EVS_BINARY_FILTER);
    
    OS_printf("GPS_PRINTER: Startup.");

    CFE_SB_CreatePipe(&gpsPipe, 10, "GPS_PRINTER_PIPE");
    // CFE_SB_Subscribe(GPS_READER_GPS_INFO_MSG,  gpsPipe);
    // CFE_SB_Subscribe(GPS_READER_GPS_GPGGA_MSG, gpsPipe);
    // CFE_SB_Subscribe(GPS_READER_GPS_GPGSA_MSG, gpsPipe);
    CFE_SB_Subscribe(GPS_READER_GPS_GPRMC_MSG, gpsPipe);
    CFE_SB_Subscribe(GPS_READER_GPS_GPVTG_MSG, gpsPipe);
}
