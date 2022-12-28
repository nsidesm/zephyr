#ifndef OTF_CONTROLLER_CFG
#define OTF_CONTROLLER_CFG

#include <stdint.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_vs.h>

// Reset the blocked PDUs to zero
void reset_blocked_pdus();

// Check if the ctrl pdu with opcode should be blocked
uint8_t is_ctrl_pdu_blocked(uint8_t opcode);

// Set blocking mask for ctrl pdus
void set_blocked_ctrl_pdu(void * blocked_ctrl_pdu);

#endif //OTF_CONTROLLER_CFG