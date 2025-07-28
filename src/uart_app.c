#include "uart_app.h"
extern system_parameter sp;
int uart_num = 0;//���ڼ�������
/* 
	���� UART9 ��ʼ�� 
	������115200
*/
void UART9_Init(void)
{
	fsp_err_t err = FSP_SUCCESS;
	err = R_SCI_UART_Open (&g_uart9_ctrl, &g_uart9_cfg);
	assert(FSP_SUCCESS == err);
}

/*������ɱ�־*/
static volatile bool uart_send_complete_flag9 = false;

/*�����жϻص�����*/
void uart9_callback (uart_callback_args_t* p_args)
{
    switch(p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            sp.uart_buffer[uart_num++] = p_args->data;
            break;
        }
        case UART_EVENT_TX_COMPLETE:
        {
            uart_send_complete_flag9 = true;
            break;
        }
        default:
            break;
    }
}

/*
	���ڽ�������
	���ܣ������յ����ַ������ͳ�ȥ
*/
void uart_proc()
{
	if(sp.uart_buffer[0] != 0){//�ַ�����Ϊ��ʱ����
		printf("%s\r\n",sp.uart_buffer);
	}
	memset(sp.uart_buffer, 0, sizeof(sp.uart_buffer));
	uart_num = 0;
}

void uart_print()
{
	sp.cpu_temper = temperature_get();
	sp.adc_data = get_adcdata();
	printf("******BEGIN******\r\n");
	printf("CPU Temperature: %0.2f\r\n", sp.cpu_temper);
	printf("ADC data:%0.2fV\r\n",sp.adc_data);
	printf("*******END*******\r\n");
}


/*�ض���printf���*/
#if defined__GNUC__ &&!defined__clang__
 int _write(int fd,char *pBuffer,int size);//��ֹ���뾯��
int _write(int fd,char *pBuffer,int size)
 {
 (void)fd;
 R_SCI_UART_Write(&g_uart4_ctrl, (uint8_t *)pBuffer,(uint32_t)size);
 while(uart_send_complete_flag== false);
 uart_send_complete_flag= false;
 return size;
 }
 #else
int fputc(int ch, FILE *f)
{
	(void)f;
	R_SCI_UART_Write(&g_uart9_ctrl, (uint8_t *)&ch, 1);
	while(uart_send_complete_flag9 == false);
	uart_send_complete_flag9 = false;
	return ch;
}
#endif