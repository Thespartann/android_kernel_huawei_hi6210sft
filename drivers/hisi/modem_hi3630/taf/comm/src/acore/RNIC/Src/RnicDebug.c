/******************************************************************************

                  ��Ȩ���� (C), 2006, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RnicDebug.c
  �� �� ��   : ����
  ��    ��   : s62952
  ��������   : 2012��01��12��
  ����޸�   :

  ��������   : RNIC������Ϣ
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2012��01��12��
    ��    ��   : s62952
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicDebug.h"
#include "RnicCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

/* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
/* modify by j00174725 for Clean Warning, 2012-07-22, Begin */
RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
/* modify by j00174725 for Clean Warning, 2012-07-22, Begin */
/* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, begin */
RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;
/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, end */

VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}

/* Added by f00179208 for DSDA Phase I, 2012-11-22, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_ShowRnicPdpStats
 ��������  : ��ʾRNIC pdp����Ϣ
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    vos_printf("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV4 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    vos_printf("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV6 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    vos_printf("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV4V6 PDP PDNID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    vos_printf("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}
/* Added by f00179208 for DSDA Phase I, 2012-11-22, End */

/*****************************************************************************
 �� �� ��  : RNIC_ShowUlProcStats
 ��������  : ��ʾRNIC����ͳ����Ϣ
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��01��12��
      ��    ��   : S62952
      �޸�����   : �����ɺ���
    2.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_ShowUlProcStats(VOS_UINT8 ucRmNetId)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* ����ͳ���� */
    vos_printf("RNIC %d����״̬                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    vos_printf("RNIC %d�յ�����IPV4���ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    vos_printf("RNIC %d�յ�����IPV6���ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    vos_printf("IPV4V6���ͼ���ʱRNIC %d�յ��������ݵĸ���IPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    vos_printf("RNIC %dδ����ʱ�յ��������ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    vos_printf("RNIC %d���з��͸�ADS���ݵĸ���                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    vos_printf("RNIC %d��ADS������������ʧ�ܵĸ���                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    vos_printf("RNIC %dδ���Ϻ�ǰ�����յ�IPV4�㲥���ĸ���              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    vos_printf("RNIC %d����ת��ΪIMM_ZCʧ�ܵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    vos_printf("RNIC %d����˽�����ݴ��󶪵��������ݰ��ĸ���            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    vos_printf("RNIC %d����ID���󶪵��������ݰ��ĸ���                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    vos_printf("RNIC %dModem ID���󶪵��������ݰ��ĸ���                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    vos_printf("RNIC %d���ض����������ݰ��ĸ���                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    vos_printf("RNIC %d�յ��������ݰ��ĸ�����ipv4ipv6��                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    vos_printf("RNIC %d�ɹ��ϱ�APP���貦��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    vos_printf("RNIC %d�ϱ�APP���貦��ʧ��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    vos_printf("RNIC %d�ɹ��ϱ�APP�Ͽ�����                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    vos_printf("RNIC %d�ϱ�APP�Ͽ�����ʧ��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RM_NET_ID_0 == ucRmNetId)
    {
        vos_printf("����ģʽ                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        vos_printf("���貦���Ƿ��ϱ��¼�                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        vos_printf("���貦�ŶϿ�ʱ��                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    vos_printf("RNIC %d RAB ID����RNIC���������ݰ�����                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    /* Added by m00217266 for L-C��������Ŀ, 2014-3-27, begin */
    vos_printf("RNIC %d PDN ID����RNIC���������ݰ�����                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);
    /* Added by m00217266 for L-C��������Ŀ, 2014-3-27, end */

    vos_printf("\r\n");

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowDLProcStats
 ��������  : ��ʾRNIC����ͳ����Ϣ
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��01��12��
      ��    ��   : S62952
      �޸�����   : �����ɺ���
    2.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* ����ͳ���� */
    vos_printf("RNIC %d�յ�����IPV4���ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    vos_printf("RNIC %d�յ�����IPV6���ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    vos_printf("RNIC %d�����������ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    vos_printf("RNIC %d������������ʧ�ܵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    vos_printf("RNIC %d�յ��������ݰ�����MTU�ĸ���                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    vos_printf("RNIC %d����δ����������ݸ���                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    vos_printf("RNIC %d���м�MACͷʧ�ܵĸ���                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    vos_printf("RNIC %d����˽�����ݴ��󶪵��������ݰ��ĸ���        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    vos_printf("RNIC %d����ID���󶪵��������ݰ��ĸ���              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
    vos_printf("RNIC %d�յ��������ݰ��ĸ�����ipv4ipv6��            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    /* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */
    vos_printf("\r\n");

    return;
}

/* Added by f00179208 for CCPU RESET, 2013-04-15, Begin */
/*****************************************************************************
 �� �� ��  : RNIC_ShowResetStats
 ��������  : ��ʾRNIC�ź�����ʼ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2013��04��15��
      ��    ��   : f00179208
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    vos_printf("ģ���ʼ����ʶ                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    vos_printf("��ǰ�Ķ������ź���                          %p\n", g_stRnicCtx.hResetSem);
    vos_printf("�����Ķ������ź���                          %p\n", g_astRnicStats[0].hBinarySemId);
    vos_printf("�����������ź���ʧ�ܴ���                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    vos_printf("���һ�����������ź���ʧ��ԭ��              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    vos_printf("��λ�ɹ��Ĵ���                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}
/* Added by f00179208 for CCPU RESET, 2013-04-15, End */

/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, begin */
/*****************************************************************************
 �� �� ��  : RNIC_Rmnet_Config_Check_Info
 ��������  : ��ӡ����������Ϣ����ʧ�ܵ�ͳ����Ϣ
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ShowRmnetConfigCheckInfo(VOS_VOID)
{
    vos_printf("Totla req                           %d\n", g_stRnicRmnetConfigCheckInfo.ucTotlaCnt);
    vos_printf("Modem type err                      %d\n", g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt);
    vos_printf("Rmnet id err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt);
    vos_printf("Modem ID err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt);
    vos_printf("Pdn ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt);
    vos_printf("Rab ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt);
    vos_printf("Rmnet status err                    %d\n", g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt);
    vos_printf("IP type err                         %d\n", g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt);
    vos_printf("Send err                            %d\n", g_stRnicRmnetConfigCheckInfo.ucSendErrCnt);
    vos_printf("Success                             %d\n", g_stRnicRmnetConfigCheckInfo.ucSuccCnt);
}
/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, end */

/*****************************************************************************
 �� �� ��  : RNIC_Help
 ��������  : RNIC������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��01��12��
      ��    ��   : S62952
      �޸�����   : �����ɺ���
    2.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_Help(VOS_VOID)
{

    vos_printf("********************RNIC������Ϣ************************\n");
    vos_printf("RNIC_ShowUlProcStats  ucRmNetId                 ��ʾָ��RNIC��������ͳ����Ϣ\n");
    vos_printf("RNIC_ShowDLProcStats  ucRmNetId                 ��ʾָ��RNIC��������ͳ����Ϣ\n");
    vos_printf("RNIC_ShowRnicPdpStats ucRmNetId                 ��ʾָ��RNIC����PDP������Ϣ\n");
    vos_printf("RNIC_ShowResetStats                             ��ʾָ��RNIC��λ״̬��Ϣ\n");

    return;
}

/* Added by A00165503 for DTS2012061904440, 2012-06-20, Begin */
/*****************************************************************************
 Function Name   : RNIC_LATENCY_OM_LOG
 Description     : A�˵Ĵ�ӡ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.z00103912      2011-6-8  Draft Enact
*****************************************************************************/
VOS_VOID RNIC_LATENCY_OM_LOG( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                           VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                           const VOS_CHAR  *pcString )
{
/* Modified by f00179208 for DSDA Phase I, 2012-11-22, Begin */
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32          ulRslt = 0;

    ulRslt = DIAG_PrintfV(DIAG_ID(ulModuleId, ulLevel), (VOS_CHAR*)pcFileName, ulLineNum, (VOS_CHAR*)("%s"), pcString);
    if (PS_SUCC != ulRslt)
    {
        return;
    }
#endif
/* Modified by f00179208 for DSDA Phase I, 2012-11-22, End */

    return;
}
/* Added by A00165503 for DTS2012061904440, 2012-06-20, End */

/*****************************************************************************
 �� �� ��  : RNIC_ShowDataDelMacHead
 ��������  : ��ӡȥ��MACͷ������
 �������  : pstSkb   :SKBUF�����׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��04��25��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowDataDelMacHead(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    vos_printf("RNIC_ShowDataDelMacHead after pull: data len is %d. \r\n", pstSkb->len);

    vos_printf("RNIC_ShowDataDelMacHead after pull: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            vos_printf("%x", pstSkb->data[i]);
        }
        else
        {
            vos_printf("0%x", pstSkb->data[i]);
        }
    }
    vos_printf("\r\n");

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowDataFromIpStack
 ��������  : ��ӡ�յ�IPЭ��ջ������
 �������  : pstSkb   :SKBUF�����׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��04��25��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    vos_printf("RNIC_ShowDataFromIpStack: data len is %d. \r\n", pstSkb->len);

    vos_printf("RNIC_ShowDataFromIpStack: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            vos_printf("%x", pstSkb->data[i]);
        }
        else
        {
            vos_printf("0%x", pstSkb->data[i]);
        }
    }

    vos_printf("\r\n");

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


