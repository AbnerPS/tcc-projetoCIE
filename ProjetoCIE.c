////////////////////////////////////////////////////////////////////////////////
/////////Integrantes: Gabriel Cardoso, Abner Pereira e Marcos.//////////////////
/////////ETEC GILDO MARÇAL BEZERRA BRANDÃO, ELETRONICA 4°Z//////////////////////
/////////Este é o programa da nossa Caixa Inteligente de Correspondência////////
////////////////////////////////////////////////////////////////////////////////

//#include <18f4520.h>

#include <16f877a.h>// Definição do microcontrolador que será usado
#use delay(clock=20000000)//Frequencia de operação (20MHz)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)//Definindo RX e TX

#fuses hs,noprotect,nobrownout,nolvp,nowdt,nocpd//Proteção e configuraçes do PIC


//#Fuses HS,NOWDT,NOPUT,NOBROWNOUT,NOLVP,NOCPD,NOWRT,NODEBUG,NOPROTECT

#define sn1 PIN_C0//Entrada do sensor 1
#define sn2 PIn_C1//entrada do sensor 2
#define sn3 PIN_C2//entrada do sensor 3
#define rst PIN_C3//RESET lcd
#define RS PIN_E0//RS do lcd
#define RW PIN_E1//RW do lcd
#define EN PIN_E2//E do lcd 
#define prog PIN_C4//Tecla de programação
#define B1 PIN_B1//Botão 1
#define B2 PIN_B2//Botão 2
#define B3 PIN_B3//Botão 3
#define B4 PIN_B4//Botão 4
#define B5 PIN_B5//Botão 5
#define B6 PIN_B6//Botão 6
#define B7 PIN_B7//Botão 7
#define pwrkey PIN_C5//Liga módulo GSM

//#define msg int

char msg1[17]={" ETEC PERUS "};//Informação que irá aparecer na primeira linha do display
char msg2[17]={" MENSAGENS ="};//Informação que irá aparecer na segunda linha do display
char msg3[17]={" PROGRAMACAO"};//Informação que irá aparecer na primeira linha do display
char msg4[17]={" TEL: "};//Informação que irá aparecer na segunda linha do display
/*char Aluno[17]={"     Alunos"};
char Gabriel[17]={"Gabriel"};
char Abner[17]={"Abner"};
char Marcos[17]={"Marcos"};
char escola1[17]={"ETEC GILDO"};
char escola2[17]={"M. B. BRANDAO"};
char Curso[17]={"ELETRONICA 4°Z"};*/

int indice1=0, indice2=0;//Variaveis de controle
int carta = 0;//Variavel "carta"

char telefone[9];//Variável telefone 
int y,x,w = 0;//variável

int msg;//variável

void escrita(int valor)//função que executa o envio de bytes ao barramento
{
output_high(EN);//pino definido como EN no estado "alto"
delay_ms(1);//Aguarda 1 ms
output_d(valor);//envia byte ao barramento de comunicação
delay_ms(1);//Aguarda 1 ms
output_low(EN);//gera borda de descida (dado armazenado na memória)
}

void teclado()//Declara que teclado sera uma sub-rotina
{
   output_low(RS);//Habilitando para receber instrução
   escrita(0x80);//Desloca o cursor para a posição inicial da primeira linha
   escrita(0x0f);//Display aceso com cursor intermitente
   output_high(RS);//Habilitando para receber dados
   
     while(msg3[indice1]!=0)//
      {
         escrita(msg3[indice1]);//
         indice1++;//indice1= indice1+1
      }
         
            output_low(RS);
            escrita(0xc0);//
            output_high(RS);
          
                  while(msg4[indice2]!=0)//
                  {
                  escrita(msg4[indice2]);//
                  indice2++;// indice2= indice2+1
                  
                  }
   x=0x20;
   output_low(RS);//Habilitando para receber instrução
   escrita(0xC6);//Declara que este "local" do display irá aparecer as funções digitadas no teclado
   output_high(RS);//Habilitando para reber dados
   while (!input(prog))//Faça enquanto for verdadeiro
   {
   indice1=0, indice2=0;
   
      delay_ms(2);//Aguarda 2 ms //
      output_high(B1);//Não há verificações na coluna 1
      output_high(B2);//Não há verificações na coluna 2
      output_low(B3);//Varredura da coluna 3
    
         if(!input(B7)&&(y<9))//Se for pressionado o B7
         {
         while(!input(B7)){}
         x=0x33;//B7 corresponde ao numero 3 se for pressionado
         telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
         if(!input(B6)&&(y<9))// Se for pressionado
         {
         while(!input(B6)){}
         x=0x36;//B6 corresponde ao numero 6 se for pressionado
          telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   } 
         if(!input(B5)&&(y<9))//Se for pressionado o B5
         {
         while(!input(B5)){}
         x=0x39;//Se for pressionado, B5 será o numero 9
                   telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
         if(!input(b4))//Se for pressionado o B4
         {
         while(!input(B4)){}//pressionado enter
         {
            y=0;
            while(y<9)
            {
            write_eeprom(y,telefone[y]);
            y++;
            }
            y=0;
            output_low(RS);
            escrita(0x01);//
            escrita(0xc7);
            output_high(RS);
            escrita("O");
            escrita("K");
            while(!input(prog))
            {
            }
         }
         
         
         while(telefone[y]!=0)
      {
         escrita(telefone[y]);
         y++;
      }
         
         y=0;
         }
         delay_ms(2);//
      
      ////////////////////////////////////////////
      
      output_high(B1);//Não há verificações na coluna 1
      output_low(B2);//Varredura da coluna 2
      output_high(B3);//Não há verificações na coluna 3
      
      if(!input(b7)&&(y<9))//Se for pressionado o B7
         {
         while(!input(B7)){}
         x=0x32;//Se for pressionado, B7 será o numero 2
                   telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      if(!input(b6)&&(y<9))//Se for pressionado o B6
         {
         while(!input(B6)){}
         x=0x35;//Se for pressionado, B6 será o numero5
                   telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      if(!input(b5)&&(y<9))//Se for pressionado o B5
         {
         while(!input(B5)){}
         x=0x38;//Se for pressionado, B5 será o numero 8
                   telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      if(!input(b4)&&(y<9))//Se for pressionado o B4
         {
         while(!input(B4)){}
         x=0x30;//Se for pressionado, B4 será o numero 0
                   telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      delay_ms(2);//Aguarda 2 ms
      
      //////////////////////////////////////////////////
      
      output_low(B1);//Varredura da coluna 2
      output_high(B2);//Não há verificações na coluna 2
      output_high(B3);//Não há verificações na coluna 3
      
      if(!input(b7)&&(y<9))//Se for pressionado o B7
         {
         while(!input(B7)){}
        x=0x31;//Se for pressionado, B7 será o numero 1
                  telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      if(!input(b6)&&(y<9))//Se for pressionado o B6
         {
         while(!input(B6)){}
         x=0x34;//Se for pressionado, B6 será o numero 4
                   telefone[y]=x;
         y++;
         escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      if(!input(b5)&&(y<9))//Se for pressionado o B5
         {
         while(!input(B5)){}
         x=0x37;//Se for pressionado, B5 será o numero 7
                   telefone[y]=x;
         y++;
      escrita(x);//tudo que for digitado no teclado, este comando será enviado para o display
   }
      if(!input(b4)&&(y<10)&&(y>0))//Se for pressionado o Backspace
         {
         while(!input(B4)){}
            output_low(RS);//
            escrita(0x04);//
            escrita(0x0f);//
            output_high(RS);//
            escrita(" ");
            y--;
            output_low(RS);//
            escrita(0x06);//
           // escrita(0x0c);//
            output_high(RS);//
   }
   }
}
void inicializa()//Inicialização do display
{
output_low(RS);//Habilitando para receber instrução 
escrita(0x38);//Configura display para 2 linhas 5x7 8 bits
escrita(0x06);//Escreve deslocando o cursor para a direita
escrita(0x0c);//Display aceso sem cursor
escrita(0x01);//Limpa display
output_high(RS);//Habilita para mandar dados
delay_ms(3);//Aguarda 3 ms
}

void reset()//Função de reset da contagem no LCD
 {
      msg=0;//
      write_eeprom(20,msg);
      output_low(RS);//configura o LCD para receber uma instrução RS=0
      escrita(0xcd);//
      output_high(RS);//configura o LCD para receber um dado RS=1
      escrita(0x20);
   }
   void valor_lcd(long int w)
{
int dezena=0x30,unidade=0x30;
        while(w>=10)
         {
         w=w-10;
         dezena++;
         }
            while(w>=1)
            {
            w=w-1;
            unidade++;
            }
output_low(RS);//configura o LCD para receber uma instrução RS=0
escrita(0xcd);//Posição que a contagem aparecerá no diplay
output_high(RS);//configura o LCD para receber um dado RS=1
escrita(dezena);//
escrita(unidade);//
}
  
void main()
{
   SETUP_CCP1(CCP_OFF);
   PORT_b_PULLUPS(true);//Ativa pullup interno do portB
   output_low(RW);//Manda nível lógico baixo neste pino do display, pois ele não será utilizado
   inicializa();//Chamada de função inicializa
   y=0;
 
            output_low(pwrkey);
            delay_ms(2500);
            output_high(pwrkey);
            msg=read_eeprom(20);
            valor_lcd(msg);
            while(y<9)
            {
           telefone[y]=read_eeprom(y);
            y++;
            }
            y=0;
while (true)//
{
            output_low(RS);
            escrita(0x80);//
            output_high(RS);
   while(msg1[indice1]!=0)//
      {
         escrita(msg1[indice1]);//
         indice1++;//indice1= indice1+1
      }
         
            output_low(RS);
            escrita(0xc0);//
            output_high(RS);
          
                  while(msg2[indice2]!=0)//
                  {
                  escrita(msg2[indice2]);//
                  indice2++;// indice2= indice2+1
                  
                  }   

            output_low(RS);
            escrita(0xce);//
            output_high(RS);
            
            //valor_lcd(msg);

   if (((input(sn1))||(input(sn2))||(input(sn3)))&&(carta == 0))//Se for acionado alguns desses sensores
   {
 //     while((input(sn1))||(input(sn2))||(input(sn3)))//só ira acionar o sensor depois
   // que a carta passar pelo mesmo.
 //  {
      while (carta == 0)
   {

   delay_ms(200);// Aguarda 2 segundos
   carta = 1;//A variável carta é verdadeira e os comando do display e do GSM serão enviados
   }
  // }
  msg++;// Incrementa mais 1 (+1) no valor do display, conforme for acionado os sensores
   write_eeprom(20,msg);//Grava o número de telefone na EEPROM interna do MCU
   valor_lcd(msg);// escreve valor no lcd
   
   
   delay_ms(250);//Aguarda 250 ms
   printf("AT\r\n");//Comando AT informa ao modem que será enviado um comando
   delay_ms(200);//Aguarda 20ms para o próximo comando
   printf("AT+CMGF=1\r\n");//Função para mandar sms
   delay_ms(200);//Aguarda 20ms para o próximo comando
   
    printf("AT+CMGS=\"%c%c%c%c%c%c%c%c%c\"\r\n",telefone[0],
    telefone[1],telefone[2],telefone[3],telefone[4],
    telefone[5],telefone[6],telefone[7],telefone[8]);  //Inserção do numero de telefone
   delay_ms(200);//Aguarda 20ms para o próximo comando
   printf("PROJETO CIE:Voce possui %u nova(s) correspondencia(s)\r\n",msg);//Mensagem a ser enviada
   delay_ms(250);//Aguarda 25ms para o próximo comando
   putc(0x1a); //Comando de envio de mensagem
   delay_ms(250);
  }
   
   if(input(rst)) 
   {
   reset();//Reset da contagem no LCD
         valor_lcd(msg);
   }
   if ((!input(sn2))&&(!input(sn3))&&(!input(sn1))) carta = 0;// Se não estiver acionado os sensores
   //a variável carta voltará a ser falsa e irá aguardar a entrada dos sensores novamente.
   
   while (!input(prog))//Faça enquanto atecla PROG for Acionada
   {
   inicializa();//Inicializa display para o modo teclado
   indice1=0, indice2=0;//Zera os valores dos indices
   teclado();//Vai para a função teclado
   inicializa();//Volta para a mensagem inicial do display
   valor_lcd(msg);//E guarda a contagem que estava anterior da quantidade das mensagens
   
   }
}
}
