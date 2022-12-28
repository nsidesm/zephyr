#include <string.h>
#include <stdlib.h>

#if defined(CONFIG_USE_SEGGER_RTT)
#include <SEGGER_RTT.h>
#endif

#include "otf_controller_cfg.h"
#include "pdu.h"
// Mask for blocked pdus
static uint8_t blocked_pdu[] = {
		0, // conn_update_ind
		0, // chan_map_ind
		0, // terminate_ind
		0, // enc_req
		0, // enc_rsp
		0, // start_enc_req
		0, // start_enc_rsp
		0, // unknown_rsp
		0, // feature_req
		0, // feature_rsp
		0, // pause_enc_req
		0, // pause_enc_rsp
		0, // version_ind
		0, // reject_ind
		0, // slave_feature_req
		0, // conn_param_req
		0, // conn_param_rsp
		0, // reject_ext_ind
		0, // ping_req
		0, // ping_rsp
		0, // length_req
		0, // length_rsp
		0, // phy_req
		0, // phy_rsp
		0, // phy_upd_ind
		0, // min_used_chans_ind
	};

void reset_blocked_pdus(){
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CONN_UPDATE_IND] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CHAN_MAP_IND] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_TERMINATE_IND] = 0;
#if defined(CONFIG_BT_CTLR_LE_ENC)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_ENC_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_ENC_RSP] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_RSP] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_RSP] = 0;
#endif /* CONFIG_BT_CTLR_LE_ENC */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_UNKNOWN_RSP] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_FEATURE_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_FEATURE_RSP] = 0;
#if defined(CONFIG_BT_REMOTE_VERSION)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_VERSION_IND] = 0;
#endif /* defined(CONFIG_BT_REMOTE_VERSION) */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_REJECT_IND] = 0;
#if defined(CONFIG_BT_CTLR_SLAVE_FEAT_REQ)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_SLAVE_FEATURE_REQ] = 0;
#endif /* PDU_DATA_LLCTRL_TYPE_SLAVE_FEATURE_REQ */
#if defined(CONFIG_BT_CTLR_CONN_PARAM_REQ)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CONN_PARAM_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CONN_PARAM_RSP] = 0;
#endif /* CONFIG_BT_CTLR_CONN_PARAM_REQ */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_REJECT_EXT_IND] = 0;
#if defined(CONFIG_BT_CTLR_LE_PING)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PING_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PING_RSP] = 0;
#endif /*CONFIG_BT_CTLR_LE_PING*/
#if defined(CONFIG_BT_CTLR_DATA_LENGTH)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_LENGTH_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_LENGTH_RSP] = 0;
#endif /* CONFIG_BT_CTLR_DATA_LENGTH */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PHY_REQ] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PHY_RSP] = 0;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PHY_UPD_IND] = 0;
#if defined(CONFIG_BT_CTLR_MIN_USED_CHAN)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_MIN_USED_CHAN_IND] = 0;
#endif /* CONFIG_BT_CTLR_MIN_USED_CHAN */
}
uint8_t is_ctrl_pdu_blocked(uint8_t opcode)
{
    uint8_t ret = blocked_pdu[opcode];
	return ret;
}

void set_blocked_ctrl_pdu(void * blocked_ctrl_pdu_ptr){
    struct bt_hci_cp_vs_set_blocked_ctrl_pdu * blocked_ctrl_pdu = (void*)blocked_ctrl_pdu_ptr;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CONN_UPDATE_IND] = blocked_ctrl_pdu->conn_update_ind;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CHAN_MAP_IND] = blocked_ctrl_pdu->chan_map_ind;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_TERMINATE_IND] = blocked_ctrl_pdu->terminate_ind;
#if defined(CONFIG_BT_CTLR_LE_ENC)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_ENC_REQ] = blocked_ctrl_pdu->enc_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_ENC_RSP] = blocked_ctrl_pdu->enc_rsp;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_REQ] = blocked_ctrl_pdu->start_enc_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_RSP] = blocked_ctrl_pdu->start_enc_rsp;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_REQ] = blocked_ctrl_pdu->pause_enc_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_START_ENC_RSP] = blocked_ctrl_pdu->pause_enc_rsp;
#endif /* CONFIG_BT_CTLR_LE_ENC */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_UNKNOWN_RSP] = blocked_ctrl_pdu->unknown_rsp;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_FEATURE_REQ] = blocked_ctrl_pdu->feature_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_FEATURE_RSP] = blocked_ctrl_pdu->feature_rsp;
#if defined(CONFIG_BT_REMOTE_VERSION)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_VERSION_IND] = blocked_ctrl_pdu->version_ind;
#endif /* defined(CONFIG_BT_REMOTE_VERSION) */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_REJECT_IND] = blocked_ctrl_pdu->reject_ind;
#if defined(CONFIG_BT_CTLR_SLAVE_FEAT_REQ)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_SLAVE_FEATURE_REQ] = blocked_ctrl_pdu->slave_feature_req;
#endif /* PDU_DATA_LLCTRL_TYPE_SLAVE_FEATURE_REQ */
#if defined(CONFIG_BT_CTLR_CONN_PARAM_REQ)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CONN_PARAM_REQ] = blocked_ctrl_pdu->conn_param_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_CONN_PARAM_RSP] = blocked_ctrl_pdu->conn_param_rsp;
#endif /* CONFIG_BT_CTLR_CONN_PARAM_REQ */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_REJECT_EXT_IND] = blocked_ctrl_pdu->reject_ext_ind;
#if defined(CONFIG_BT_CTLR_LE_PING)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PING_REQ] = blocked_ctrl_pdu->ping_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PING_RSP] = blocked_ctrl_pdu->ping_rsp;
#endif /*CONFIG_BT_CTLR_LE_PING*/
#if defined(CONFIG_BT_CTLR_DATA_LENGTH)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_LENGTH_REQ] = blocked_ctrl_pdu->length_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_LENGTH_RSP] = blocked_ctrl_pdu->length_rsp;
#endif /* CONFIG_BT_CTLR_DATA_LENGTH */
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PHY_REQ] = blocked_ctrl_pdu->phy_req;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PHY_RSP] = blocked_ctrl_pdu->phy_rsp;
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_PHY_UPD_IND] = blocked_ctrl_pdu->phy_upd_ind;
#if defined(CONFIG_BT_CTLR_MIN_USED_CHAN)
    blocked_pdu[PDU_DATA_LLCTRL_TYPE_MIN_USED_CHAN_IND] = blocked_ctrl_pdu->min_used_chan_ind;
#endif /* CONFIG_BT_CTLR_MIN_USED_CHAN */
}