/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : AtCmdFtmProc.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2013��3��13��
  ����޸�   :
  ��������   : ���̲���������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��13��
    ��    ��   : l60609
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtCmdFtmProc.h"
#include "ATCmdProc.h"
#include "AtMtaInterface.h"

/* Added by z60575 for LOG35_TL, 2013-8-9 begin */
#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
#endif
/* Added by z60575 for LOG35_TL, 2013-8-9 end */

#include "AtTestParaCmd.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_FTM_PROC_C
/*lint +e767 +e960*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : At_SetLogPortPara
 ��������  : ^LOGPORT�����ú���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��9��
    ��    ��   : z60575
    �޸�����   : LOG35_TL����TL�ӿ�
*****************************************************************************/
VOS_UINT32 At_SetLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulOmLogPort;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ���������û�� */
    if ((2 < gucAtParaIndex) || (0 == gucAtParaIndex))
    {
        return AT_ERROR;
    }

    if (AT_LOG_PORT_USB == gastAtParaList[0].ulParaValue)
    {
        ulOmLogPort = CPM_OM_PORT_TYPE_USB;
    }
    else
    {
        ulOmLogPort = CPM_OM_PORT_TYPE_VCOM;
    }

    /* ����ֻ��һ����Ĭ��������Ч */
    if (1 == gucAtParaIndex)
    {
        gastAtParaList[1].ulParaValue = VOS_TRUE;
    }

    /* ����OM�Ľӿ� */
    ulRslt = PPM_LogPortSwitch(ulOmLogPort, gastAtParaList[1].ulParaValue);

    if (VOS_OK == ulRslt)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : At_QryLogPortPara
 ��������  : ^LOGPORT�Ĳ�ѯ����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��9��
    ��    ��   : z60575
    �޸�����   : LOG35_TL����TL�ӿ�
*****************************************************************************/
VOS_UINT32 At_QryLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulOmLogPort;
    VOS_UINT32                          ulAtLogPort;
    VOS_UINT32                          ulRslt;

    usLength                            = 0;
    ulOmLogPort                         = AT_LOG_PORT_USB;

    ulRslt = PPM_QueryLogPort(&ulOmLogPort);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    if (COMM_LOG_PORT_USB == ulOmLogPort)
    {
        ulAtLogPort = AT_LOG_PORT_USB;
    }
    else
    {
        ulAtLogPort = AT_LOG_PORT_VCOM;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulAtLogPort);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/* Added by g00261581 for Jazz DPDT, 2014-04-04, begin */
/*****************************************************************************
 �� �� ��  : At_SetDpdtTestFlagPara
 ��������  : ֧��^DPDTTEST���ã�
             �����ʽ:^DPDTTEST=<RatMode>,<Flag>
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��04��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_SetDpdtTestFlagPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU   stAtCmd;
    VOS_UINT32                          ulRst;

    /* ������� */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT������MTA����Ϣ�ṹ��ֵ */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucFlag    = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_DPDTTEST_FLAG_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTTEST_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : At_SetDpdtPara
 ��������  : ֧��^DPDT���ã�
             �����ʽ:^DPDT=<RatMode>,<DpdtValue>
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��04��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_SetDpdtPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_DPDT_VALUE_REQ_STRU      stAtCmd;
    VOS_UINT32                          ulRst;

    /* ������� */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT������MTA����Ϣ�ṹ��ֵ */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode   = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ulDpdtValue = gastAtParaList[1].ulParaValue;

    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_DPDT_VALUE_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_DPDT_VALUE_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDT_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
 �� �� ��  : At_SetQryDpdtPara
 ��������  : ֧��^DPDTQRY���ã�
             �����ʽ:^DPDTQRY=<RatMode>
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��04��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_SetQryDpdtPara(VOS_UINT8 ucIndex)
{
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU      stAtCmd;
    VOS_UINT32                          ulRst;

    /* ������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT������MTA����Ϣ�ṹ��ֵ */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU));
    stAtCmd.enRatMode = (AT_MTA_CMD_RATMODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_QRY_DPDT_VALUE_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_QRY_DPDT_VALUE_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DPDTQRY_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetDpdtTestFlagCnf
 ��������  : ATģ���յ�MTA�ظ���Set Dpdt Flag�ظ���Ϣ�Ĵ�������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��09��
    ��    ��   : g00261581
    �޸�����   : �½�
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetDpdtTestFlagCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg         = VOS_NULL_PTR;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU  *pstSetDpdtFlagCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex   = 0;
    pstMtaMsg = (AT_MTA_MSG_STRU *)pMsg;
    pstSetDpdtFlagCnf = (MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_DPDTTEST_SET */
    if (AT_CMD_DPDTTEST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtTestFlagCnf: WARNING:Not AT_CMD_DPDTTEST_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if (MTA_AT_RESULT_NO_ERROR == pstSetDpdtFlagCnf->enResult)
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetDpdtValueCnf
 ��������  : ATģ���յ�MTA�ظ���Set Dpdt Value�ظ���Ϣ�Ĵ�������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��09��
    ��    ��   : g00261581
    �޸�����   : �½�
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetDpdtValueCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU     *pstSetDpdtValueCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex            = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstSetDpdtValueCnf = (MTA_AT_SET_DPDT_VALUE_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_DPDT_SET */
    if (AT_CMD_DPDT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetDpdtValueCnf: WARNING:Not AT_CMD_DPDT_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if (MTA_AT_RESULT_NO_ERROR == pstSetDpdtValueCnf->enResult)
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaQryDpdtValueCnf
 ��������  : ATģ���յ�MTA�ظ���Qry Dpdt Value�ظ���Ϣ�Ĵ�������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��09��
    ��    ��   : g00261581
    �޸�����   : �½�
*****************************************************************************/
VOS_UINT32 AT_RcvMtaQryDpdtValueCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg          = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU     *pstQryDpdtValueCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex            = 0;
    pstMtaMsg          = (AT_MTA_MSG_STRU *)pMsg;
    pstQryDpdtValueCnf = (MTA_AT_QRY_DPDT_VALUE_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_DPDTQRY_SET */
    if (AT_CMD_DPDTQRY_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryDpdtValueCnf: WARNING:Not AT_CMD_DPDTQRY_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if (MTA_AT_RESULT_NO_ERROR == pstQryDpdtValueCnf->enResult)
    {
        ulResult = AT_OK;
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "^DPDTQRY: %d",
                                            pstQryDpdtValueCnf->ulDpdtValue);
    }
    else
    {
        ulResult = AT_ERROR;
        gstAtSendData.usBufLen = 0;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
/* Added by g00261581 for Jazz DPDT, 2014-04-04, End */

/* Added by g00261581 for V3R3 JAM DETECT Project, 2014-05-04, begin */
/*****************************************************************************
 �� �� ��  : At_SetJamDetectPara
 ��������  : ֧��^JDETEX����
             �����ʽ:^JDETEX=<mode>[,<METHOD>,<NPT>,<UCN>]
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��05��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_SetJamDetectPara(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_JAM_DETECT_REQ_STRU      stAtCmd;
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamCfg;
    VOS_UINT32                          ulRst;

    /* ������� */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT������MTA����Ϣ�ṹ��ֵ */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU));

    stAtCmd.ucFlag         = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stAtCmd.ucMethod       = AT_JAM_DETECT_DEFAULT_METHOD;

    if (0 == gastAtParaList[2].usParaLen)
    {
        stAtCmd.ucThreshold    = AT_JAM_DETECT_DEFAULT_THRESHOLD;
    }
    else
    {
        stAtCmd.ucThreshold    = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    }

    if (0 == gastAtParaList[3].usParaLen)
    {
        stAtCmd.ucFreqNum      = AT_JAM_DETECT_DEFAULT_FREQ_NUM;
    }
    else
    {
        stAtCmd.ucFreqNum      = (VOS_UINT8)gastAtParaList[3].ulParaValue;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_JAM_DETECT_CFG, &stNvJamCfg, sizeof(stNvJamCfg)))
    {
        AT_WARN_LOG("At_SetJamDetectPara():en_NV_Item_JAM_DETECT_CFG NV Read Fail!");
        return AT_ERROR;
    }

    /* ���ò���������NV��Ϣ�ṹ�� */
    stNvJamCfg.ucMode      = stAtCmd.ucFlag;
    stNvJamCfg.ucMethod    = stAtCmd.ucMethod;
    stNvJamCfg.ucThreshold = stAtCmd.ucThreshold;
    stNvJamCfg.ucFreqNum   = stAtCmd.ucFreqNum;

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_JAM_DETECT_CFG, &stNvJamCfg, sizeof(stNvJamCfg)))
    {
        AT_WARN_LOG("At_SetJamDetectPara():en_NV_Item_JAM_DETECT_CFG NV Write Fail!");
        return AT_ERROR;
    }

    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_JAM_DETECT_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_JAM_DETECT_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_JDETEX_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : At_QryJamDetectPara
 ��������  : ^JDETEX��ѯJam Detect����ֵ
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : ִ�н��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��9��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 At_QryJamDetectPara(VOS_UINT8 ucIndex)
{
    NV_NAS_JAM_DETECT_CFG_STRU          stNvJamDetect;

    PS_MEM_SET(&stNvJamDetect, 0x0, sizeof(stNvJamDetect));

    /* ͨ����ȡNV����ȡJam Detect��ǰ����ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_JAM_DETECT_CFG,
                           &stNvJamDetect,
                           sizeof(NV_NAS_JAM_DETECT_CFG_STRU)))
    {
        AT_WARN_LOG("At_QryJamDetectPara: NV_ReadEx en_NV_Item_JAM_DETECT_CFG fail!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stNvJamDetect.ucMode,
                                                    stNvJamDetect.ucMethod,
                                                    stNvJamDetect.ucThreshold,
                                                    stNvJamDetect.ucFreqNum);

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetJamDetectCnf
 ��������  : ATģ���յ�MTA�ظ���Jam Detect���ý����������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetJamDetectCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg;
    MTA_AT_SET_JAM_DETECT_CNF_STRU         *pstSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_JAM_DETECT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_JDETEX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetJamDetectCnf : Current Option is not AT_CMD_JDETEX_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaJamDetectInd
 ��������  : ATģ���յ�MTA�ظ���Jam Ind�ϱ���Ϣ��������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��6��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaJamDetectInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_JAM_DETECT_IND_STRU         *pstJamDetectInd;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstJamDetectInd     = (MTA_AT_JAM_DETECT_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaJamDetectInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    /* �ϱ����ż���� */
    if (MTA_AT_JAM_RESULT_JAM_DISCOVERED == pstJamDetectInd->enJamResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^JDET: JAMMED%s",
                                                        gaucAtCrLf,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }

    if (MTA_AT_JAM_RESULT_JAM_DISAPPEARED == pstJamDetectInd->enJamResult)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^JDET: DETECTING%s",
                                                        gaucAtCrLf,
                                                        gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    return VOS_OK;
}
/* Added by g00261581 for V3R3 JAM DETECT Project, 2014-05-04, end */

/* Added by g00261581 for V7R11 FREQ LOCK Project, 2014-06-11, begin */
/*****************************************************************************
 �� �� ��  : AT_SetRatFreqLock
 ��������  : ֧��^FREQLOCK����
             �����ʽ:^FREQLOCK=<enable>[,<freq>[,<ratMode>[,<band>]]]
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��11��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetRatFreqLock(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_FREQ_LOCK_REQ_STRU       stAtCmd;
    VOS_UINT32                          ulRst;

    /* ����������� */
    if ((gucAtParaIndex < 1) || (gucAtParaIndex > 4))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU));
    stAtCmd.ucEnableFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �����Ƶ���ܹرգ�ֱ��дNv, ����AT_OK */
    if (VOS_FALSE == stAtCmd.ucEnableFlg)
    {
        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_FREQ_LOCK_CFG, &stAtCmd, sizeof(stAtCmd)))
        {
            AT_ERR_LOG("AT_SetRatFreqLock(): en_NV_Item_FREQ_LOCK_CFG NV Write Fail!");
            return AT_ERROR;
        }

        return AT_OK;
    }

    stAtCmd.usLockedFreq = (VOS_UINT16)gastAtParaList[1].ulParaValue;

    /* ���������еĽ���ģʽ */
    if (0 == gastAtParaList[2].usParaLen)
    {
        stAtCmd.enRatMode = AT_MTA_FREQLOCK_RATMODE_WCDMA;
    }
    else
    {
        stAtCmd.enRatMode = (AT_MTA_FREQLOCK_RATMODE_ENUM_UINT8)gastAtParaList[2].ulParaValue;
    }

    /* ���������е�BAND��Ϣ */
    if (0 == gastAtParaList[3].usParaLen)
    {
        if (AT_MTA_FREQLOCK_RATMODE_GSM == stAtCmd.enRatMode)
        {
            return AT_ERROR;
        }
        stAtCmd.enBand = AT_MTA_GSM_BAND_BUTT;
    }
    else
    {
        stAtCmd.enBand = (AT_MTA_GSM_BAND_ENUM_UINT16)gastAtParaList[3].ulParaValue;
    }

    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_FREQ_LOCK_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_SET_FREQ_LOCK_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RATFREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetRatFreqLockCnf
 ��������  : ATģ���յ�MTA�ظ���Ƶ��������������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��12��
    ��    ��   : g00261581
    �޸�����   : ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetRatFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_FREQ_LOCK_CNF_STRU      *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_FREQ_LOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_RATFREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetRatFreqLockCnf : Current Option is not AT_CMD_RATFREQLOCK_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_QryRatFreqLock
 ��������  : ^FREQLOCK��ѯ��Ƶ��������ֵ
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : ִ�н��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��12��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_QryRatFreqLock(VOS_UINT8 ucIndex)
{
    TAF_NVIM_FREQ_LOCK_CFG_STRU         stNvFreqLockCfg;

    PS_MEM_SET(&stNvFreqLockCfg, 0x0, sizeof(stNvFreqLockCfg));

    /* ͨ����ȡNV����ȡFreq Lock��ǰ����ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_FREQ_LOCK_CFG,
                           &stNvFreqLockCfg,
                           sizeof(TAF_NVIM_FREQ_LOCK_CFG_STRU)))
    {
        AT_WARN_LOG("At_QryRatFreqLock: NV_ReadEx en_NV_Item_FREQ_LOCK_CFG fail!");
        return AT_ERROR;
    }

    /* ��Ƶ���ܹر������ֻ�ϱ�����ֵ:0 */
    if (VOS_FALSE == stNvFreqLockCfg.ucEnableFlg)
    {
        /* ��ѯ����ϱ� */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg);

        return AT_OK;
    }

    /* ��Ƶ����������Gģ�ϣ���ѯ��Ҫ�ϱ�BAND��Ϣ */
    if (TAF_NVIM_RAT_MODE_GSM == stNvFreqLockCfg.enRatMode)
    {
        /* ��ѯ����ϱ� */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,\"0%d\",\"0%d\"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg,
                                                        stNvFreqLockCfg.usLockedFreq,
                                                        stNvFreqLockCfg.enRatMode,
                                                        stNvFreqLockCfg.enBand);
    }
    else
    {
        /* ��ѯ����ϱ� */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d,%d,\"0%d\"",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        stNvFreqLockCfg.ucEnableFlg,
                                                        stNvFreqLockCfg.usLockedFreq,
                                                        stNvFreqLockCfg.enRatMode);
    }

    return AT_OK;
}
/* Added by g00261581 for V7R11 FREQ LOCK Project, 2014-06-11, end */

/* Added by j00174725 for GU ROAD TEST, 2014-08-05, Begin */
/*****************************************************************************
 �� �� ��  : AT_SetGFreqLock
 ��������  : ֧��^GFREQLOCK����
             �����ʽ:^GFREQLOCK =<enable>[,<freq>,<band>]
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��08��05��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetGFreqLock(VOS_UINT8 ucIndex)
{
    AT_MTA_SET_GSM_FREQLOCK_REQ_STRU    stGFreqLockInfo;
    VOS_UINT32                          ulRst;

    /* ����������� */
    if ((gucAtParaIndex != 1) && (gucAtParaIndex != 3))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stGFreqLockInfo, 0, sizeof(AT_MTA_SET_GSM_FREQLOCK_REQ_STRU));

    /* ������Ч�Լ�� */
    /* ��һ����������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stGFreqLockInfo.enableFlag = (PS_BOOL_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* ��������Ƶ���������ڶ��������͵��������� */
    if (PS_TRUE == stGFreqLockInfo.enableFlag)
    {
        if ( (0 == gastAtParaList[1].usParaLen)
          || (0 == gastAtParaList[2].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            stGFreqLockInfo.usFreq = (VOS_UINT16)gastAtParaList[1].ulParaValue;
            stGFreqLockInfo.enBand = (AT_MTA_GSM_BAND_ENUM_UINT16)gastAtParaList[2].ulParaValue;
        }
    }

    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_SET_GSM_FREQLOCK_REQ,
                                   &stGFreqLockInfo,
                                   sizeof(AT_MTA_SET_GSM_FREQLOCK_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GSM_FREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_RcvMtaSetGFreqLockCnf
 ��������  : ATģ���յ�MTA�ظ���GģƵ�����ý����������
 �������  : pstMsg -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��08��05��
    ��    ��   : j00174725
    �޸�����   : ����
*****************************************************************************/
VOS_UINT32 AT_RcvMtaSetGFreqLockCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SET_GSM_FREQLOCK_CNF_STRU   *pstSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf    = (MTA_AT_SET_GSM_FREQLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex      = 0;
    ulResult     = AT_ERROR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_GSM_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetGFreqLockCnf : Current Option is not AT_CMD_GSM_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR == pstSetCnf->enResult)
    {
        ulResult = AT_OK;
    }

    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}

/* Added by j00174725 for GU ROAD TEST, 2014-08-05, End */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
