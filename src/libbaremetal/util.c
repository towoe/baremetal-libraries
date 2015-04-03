#include "include/optimsoc-baremetal.h"

uint32_t optimsoc_get_numct(void) {
  return REG32(OPTIMSOC_NA_CT_NUM);
}

int optimsoc_get_ctrank(void) {
  return optimsoc_get_tilerank(optimsoc_get_tileid());
}


int optimsoc_get_tilerank(unsigned int tile) {
	uint16_t *ctlist = (uint16_t*) OPTIMSOC_NA_CT_LIST;
	for (int i = 0; i < optimsoc_get_numct(); i++) {
		if (REG16(&ctlist[i]) == tile) {
			return i;
		}
	}
	return -1;
}

int optimsoc_get_ranktile(unsigned int rank) {
    uint16_t *ctlist = (uint16_t*) OPTIMSOC_NA_CT_LIST;
    return ctlist[rank];
}

void optimsoc_init(optimsoc_conf *config) {

}

uint32_t optimsoc_mainmem_size() {
  return OPTIMSOC_NA_GMEM_SIZE;
}

uint32_t optimsoc_mainmem_tile() {
  return OPTIMSOC_NA_GMEM_TILE;
}

uint32_t optimsoc_noc_maxpacketsize(void) {
  return 8;
}

void optimsoc_trace_definesection(int id, char* name) {
  OPTIMSOC_TRACE(0x20,id);
  while (*name!=0) {
      OPTIMSOC_TRACE(0x21,*name);
      name = name + 1;
  }
}

void optimsoc_trace_defineglobalsection(int id, char* name) {

}

void optimsoc_trace_section(int id) {
  OPTIMSOC_TRACE(0x22,id);
}

void optimsoc_trace_kernelsection(void) {
  OPTIMSOC_TRACE(0x23,0);
}

void optimsoc_mutex_init(optimsoc_mutex_t **mutex) {
    **mutex = 0;
}

void optimsoc_mutex_lock(optimsoc_mutex_t *mutex) {
    while (or1k_sync_tsl(mutex) != 0) {}
}

void optimsoc_mutex_unlock(optimsoc_mutex_t *mutex) {
    *mutex = 0;
}
