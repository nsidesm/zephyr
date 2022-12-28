#include <stdint.h>
/**
 * Public interface for mitm funtions
 * */

int public_ctrl_pdu_send(uint8_t opcode, uint8_t length, uint8_t *data);

uint8_t ll_feature_req_send(uint16_t handle);

uint8_t ll_version_ind_send(uint16_t handle);