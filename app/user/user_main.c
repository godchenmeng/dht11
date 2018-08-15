#include "ets_sys.h"
#include "osapi.h"
#include "ip_addr.h"
#include "mem.h"
#include "user_interface.h"
#include "c_types.h"
#include "dht.h"

os_timer_t os_timer;

void hw_test_timer_cb(void) {

	pollDHTCb();
	os_printf("dht11�ɼ����¶�= %d ,�¶�= %d %%\r\n\n", wendu, shidu);

	os_printf("- - - - - - - - - - - - - - - - - - - - \r\n");
}

void ICACHE_FLASH_ATTR user_init(void) {

	uart_init(57600, 57600);
	os_printf("SDK version:%s\n", system_get_sdk_version());

	DHTInit(SENSOR_DHT11);
	wendu = shidu = 0; //��ʼ����ʪ��Ϊ0

	/** �رոö�ʱ�� */
	os_timer_disarm(&os_timer);
	/** ���øö�ʱ���ص����� */
	os_timer_setfn(&os_timer, (ETSTimerFunc *) (hw_test_timer_cb), NULL);
	/** �����ö�ʱ�� */
	os_timer_arm(&os_timer, 1500, true);

}

uint32 ICACHE_FLASH_ATTR user_rf_cal_sector_set(void) {
	enum flash_size_map size_map = system_get_flash_size_map();
	uint32 rf_cal_sec = 0;

	switch (size_map) {
	case FLASH_SIZE_4M_MAP_256_256:
		rf_cal_sec = 128 - 5;
		break;

	case FLASH_SIZE_8M_MAP_512_512:
		rf_cal_sec = 256 - 5;
		break;

	case FLASH_SIZE_16M_MAP_512_512:
	case FLASH_SIZE_16M_MAP_1024_1024:
		rf_cal_sec = 512 - 5;
		break;

	case FLASH_SIZE_32M_MAP_512_512:
	case FLASH_SIZE_32M_MAP_1024_1024:
		rf_cal_sec = 1024 - 5;
		break;

	case FLASH_SIZE_64M_MAP_1024_1024:
		rf_cal_sec = 2048 - 5;
		break;
	case FLASH_SIZE_128M_MAP_1024_1024:
		rf_cal_sec = 4096 - 5;
		break;
	default:
		rf_cal_sec = 0;
		break;
	}
	return rf_cal_sec;
}

void ICACHE_FLASH_ATTR user_rf_pre_init(void) {
}
