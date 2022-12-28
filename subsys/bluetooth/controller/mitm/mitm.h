#ifndef MITM
#define MITM

#include <stdint.h>

/* Flag to idicate MitM is active */
extern uint8_t MITM_ON;
/* Flag to indicate sending of a mitm PDU */
extern uint8_t MITM_ENC_ON;

//struct mitm_data_store *get_mitm_ds();

uint8_t *mitm_get_rand();
void mitm_set_rand(uint8_t *rand);

uint8_t *mitm_get_ediv();
void mitm_set_ediv(uint8_t *ediv);

uint8_t *mitm_get_skdm();
void mitm_set_skdm(uint8_t *skdm);

uint8_t *mitm_get_ivm();
void mitm_set_ivm(uint8_t *ivm);

uint8_t *mitm_get_skds();
void mitm_set_skds(uint8_t *skds);

uint8_t *mitm_get_ivs();
void mitm_set_ivs(uint8_t *ivs);

uint8_t mitm_ctrl_pdu_send(uint8_t opcode, uint8_t length, uint8_t *data);

uint8_t mitm_enc_req_send(uint16_t handle);

uint8_t mitm_enc_rsp_send(uint16_t handle);

uint8_t mitm_start_enc_rsp_send(uint16_t handle);

uint8_t mitm_start_enc_req_send(uint16_t handle);

uint8_t mitm_pause_enc_rsp_send(uint16_t handle);

uint8_t mitm_pause_enc_req_send(uint16_t handle);

uint8_t mitm_reject_ext_ind_send(uint16_t handle);

uint8_t mitm_reject_ind_send(uint16_t handle);

uint8_t mitm_enc_send_ctrl(uint8_t len, uint8_t opcode, uint8_t * data, uint16_t handle);

uint8_t mitm_feature_req_send(uint16_t handle);

uint8_t mitm_version_ind_send(uint16_t handle);
#endif /* MITM */
