#include <string.h>
#include <stdlib.h>
#include "ull_conn.h"
#include "mitm.h"

/* Flag to idicate MitM is active */
uint8_t MITM_ON = 0U;
/* Flag to indicate sending of a mitm PDU */
uint8_t MITM_ENC_ON = 0U;

uint8_t mitm_ctrl_pdu_send(uint8_t opcode, uint8_t length, uint8_t *data)
{
	uint8_t ret = public_ctrl_pdu_send(opcode, length, data);

	return ret;
}

uint8_t mitm_feature_req_send(uint16_t handle)
{
	uint8_t ret = ll_feature_req_send(handle);

	return ret;
}

uint8_t mitm_version_ind_send(uint16_t handle)
{
	uint8_t ret = ll_version_ind_send(handle);

	return ret;
}