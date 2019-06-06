#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>


/*
-------------------------------------
*      COMMIT DIA 26/11/2018        *
*        DEV WAGNER NEVES           *
*        DEV IGOR HENRIQUE          *
-------------------------------------
*/

void logo()
{
    system("cls");
    printf("\n*****************************************************************************************************************");
    printf("\n*****************************************************************************************************************\n");
    printf("\n\t  $$$$$   $$$     $$$    $$$$$$$$   $$$$$$$    $$$$$$$$    $$$$$$$$     $$$$$$$$    $$$     $$$                    ");
    printf("\n\t $$       $$$$   $$$$    $$    $$   $$    $$   $$$$$$$$    $$     $$    $$$$$$$$    $$$$   $$$$                    ");
    printf("\n\t $$	  $$  $ $  $$    $$    $$   $$    $$      $$       $$     $$       $$       $$  $ $  $$                    ");
    printf("\n\t  $$$$    $$   $   $$    $$$$$$$$   $$$$$$$       $$       $$$$$$$         $$       $$   $   $$                    ");
    printf("\n\t     $$   $$       $$    $$    $$   $$  $$        $$       $$              $$       $$       $$                    ");
    printf("\n\t     $$   $$       $$    $$    $$   $$   $$       $$       $$           $$$$$$$$    $$       $$                    ");
    printf("\n\t $$$$$    $$       $$    $$    $$   $$    $$      $$       $$           $$$$$$$$    $$       $$                  \n");

    printf("\n*****************************************************************************************************************");

    printf("\n************************************ |A MELHOR SOLUCAO PARA SEU NEGOCIO| ****************************************\n\n\n");

}


/*
---------------------
* VARIAVEIS GLOBAIS *
---------------------
*/


int Opcao;  //MENU INICIAL.
int cadas; // MENU CADASTRO.
int rept;//USADA PARA VERIFICAR SE O USUARIO DESEJA CADASTRAR UM NOVO PRODUTO NO LAÇO DE REPETIÇÃO.
char codigo[100]; // VARIAVEL DE COMPARAÇÃO PARA A BUSCA DO PRODUTO.
char nomProduto[100];// NOME DO PRODUTO PARA O CADASTRO.
float valor;// VALOR DO PRODUTO PARA O CADASTRO.

int qtdItem;
float itemXprecoUltimo;
float preco = 0.00;
float itemXpreco =0.00;
float valorTotalCompra = 0.00;


/*
------------------------------------
* STRUCT PARA CADASTRO DE PRODUTOS *WN
------------------------------------
*/
typedef struct Produtos
{
    char linha[121], codigo[25], nomProduto[101], valor[25];
    struct Produtos *inicioPro;
    struct Produtos *proximoPro;
} Produtos;
Produtos *inicioPro = NULL;



/*
---------------------------------------------------------
* FUNCAO PARA IMPORTAR ARQUIVO COM CADASTRO DE PRODUTOS *WN
---------------------------------------------------------
*/

void importaProdutos()
{
    char linha[121], codigo[25], nomProduto[101], valor[25];
    FILE *arq;
    arq = fopen("estoqueProdutos.txt","r");
    if (arq == NULL)
    {

        fprintf(stderr, "*****************************************************************************************************************\n");
        fprintf(stderr, "*                                                                                                               *\n");
        fprintf(stderr, "*                                         >>>>> AVISO! <<<<<                                                    *\n");
        fprintf(stderr, "*                            >>>>> SEM PRODUTOS CADASTRADOS PARA VENDA! <<<<<                                   *\n");
        fprintf(stderr, "*                                                                                                               *\n");
        fprintf(stderr, "*****************************************************************************************************************\n\n\n");

        system("pause");
        system("cls");
        return 1;
    }

    while (!feof(arq))
    {
        memset(linha, '\0', (sizeof(linha)));
        memset(codigo, '\0', (sizeof(codigo)));
        memset(nomProduto, '\0', (sizeof(nomProduto)));
        memset(valor, '\0', (sizeof(valor)));
        fgets(linha, "%121s", arq);
        if (linha[1] == NULL)
        {
            break;
        }
        char *Ponteiro = NULL;
        Ponteiro = strtok(linha, "|");
        strcat(codigo, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(nomProduto, Ponteiro);
        Ponteiro = strtok(NULL, "|");
        strcat(valor, Ponteiro);
        Ponteiro = strtok(NULL, "|");

        Produtos *produto = (Produtos*) malloc(sizeof(Produtos));
        strcpy(produto->codigo, codigo);
        strcpy(produto->nomProduto, nomProduto);
        strcpy(produto->valor, valor);
        produto->proximoPro = NULL;
        if (produto == NULL)
        {
            inicioPro = produto;
        }
        else
        {
            produto->proximoPro = inicioPro;
            inicioPro = produto;
        }
    }
    fclose(arq);
}

/*
-------------------------------------------------------
* FUNCAO PARA LIBERAR MEMORIA DOS PRODUTOS IMPORTADOS *WN
-------------------------------------------------------
*/
void limpaMemoria()
{

    free(inicioPro);
    inicioPro = NULL;

}


/*
-----------------------------------------------
* FUNCAO QUE RETORNA OPCAO INVALIDA NOS MENUS *WN
-----------------------------------------------
*/
void invalido()
{
    printf("\nOpcao invalida, tente novamente\n\n\n\n");
    system("pause");
    system("cls");
}


/*
-----------------------------------------
* FUNCAO PARA IMPRIMIR COMPRA CANCELADA *WN
-----------------------------------------
*/
void exibeCompraCancelada()
{
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                       >>>>> COMPRA CANCELADA <<<<<                                            *\n");
    printf("*                                       >>>>>   COM  SUCESSO ! <<<<<                                            *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

    printf("\n\n --->Retornando...<---\n\n");

}

/*
--------------------------------------------
* FUNCAO PARA IMPRIMIR CANCELA RECEBIMENTO *WN
--------------------------------------------
*/
void exibeCancelaRecebimento()
{
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                     >>>>> RECEBIMENTO CANCELADO <<<<<                                         *\n");
    printf("*                                       >>>>>   COM  SUCESSO ! <<<<<                                            *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

}


/*
--------------------------------------
* FUNCAO PARA IMPRIMIR ITEM REMOVIDO *WN
--------------------------------------
*/
void exibeItemRemovido()
{
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                           >>>>> ITEM REMOVIDO <<<<<                                           *\n");
    printf("*                                           >>>>> COM  SUCESSO! <<<<<                                           *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

}

void exibeTrocoMenor()
{
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*              >>>>> O VALOR DO DINHEIRO DIGITADO E MENOR QUE O VALOR DA COMPRA <<<<<                           *\n");
    printf("*                          >>>>> FAVOR INICIAR O RECEBIMENTO NOVAMENTE <<<<<                                    *\n");
    printf("*                       >>>>> SELECIONANDO A OPCAO 3 - RECEBER COMPRA ! <<<<<                                   *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

}

/*
-------------------------
* FUNCAO MENU PRINCIPAL *WN
-------------------------
*/
void exibeMenuPrincipal()
{
    system("cls");


    int op;

    do{

    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                        >>>>> MENU PRINCIPAL VENDAS<<<<<                                       *\n");
    printf("*                                                                                                               *\n");
    printf("*                                              0 - Retornar                                                     *\n");
    printf("*                                              1 - Vender                                                       *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

    printf("\nDigite uma opcao: ");
    scanf("%d", &op);


    if (op == 0)
    {
        printf("\n\n --->Retornando...<---\n\n");
        system("pause");
        limpaMemoria();
    }

    else if (op ==1)
    {
        exibeMenuVendaCompleto();
    }

    else
    {
        invalido();
    }

    }while(op!=0);
}


/*
----------------------------------
* FUNCAO MENU COMPLETO DE VENDAS *WN
----------------------------------
*/
void exibeMenuVendaCompleto()
{
    int op;
    int removItem = 0;
    int item[500];
    Produtos *aux = inicioPro;
    char codigo[25];
    int controlPesquisa = 0;


    do
    {

        system("cls");
        printf("\n\t\t\t\t\t   Valor total da compra:%.2f \n", valorTotalCompra);
        printf("\n\t\t\t\t\t   Ultimo Valor Inserido:%.2f \n", itemXpreco);

        printf("*****************************************************************************************************************\n");
        printf("*                                                                                                               *\n");
        printf("*                                          >>>>> MENU VENDA <<<<<                                               *\n");
        printf("*                                                                                                               *\n");
        printf("*                                          0 - Cancelar Compra e voltar                                         *\n");
        printf("*                                          1 - Incluir Item                                                     *\n");
        printf("*                                          2 - Remover o ultimo Item                                            *\n");
        printf("*                                          3 - Receber Compra                                                   *\n");
        printf("*                                                                                                               *\n");
        printf("*****************************************************************************************************************\n");

        printf("\nDigite uma opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            exibeCompraCancelada();
            system("pause");
            system("cls");
            valorTotalCompra = 0.00;
            itemXpreco = 0.00;
            limpaMemoria();
            break;
        case 1:
            controlPesquisa = 0;
            printf("\nPesquisar\n");
            fflush(stdin);
            printf("\nEntre com o codigo do Produto: ");
            fgets(codigo, sizeof(codigo), stdin);
            codigo[strcspn(codigo, "\n")]='\0';

            while(aux != NULL)
            {
                if ((strcmp(codigo, aux->codigo)) == 0)
                {

                    printf("\n\n");

                    printf("Codigo: %s\nProduto: %s\nValor: %s\n\n",aux->codigo, aux->nomProduto, aux->valor);
                    preco =  atof(aux->valor);
                    controlPesquisa = 1;
                }
                aux = aux->proximoPro;

            }
            aux = inicioPro;

            if (controlPesquisa == 1)
            {
                printf("\nDigite a quantidade de Item: ");
                scanf("%d", &qtdItem);
                itemXpreco = qtdItem * preco;
                itemXprecoUltimo = itemXpreco;
                removItem = 1;
                valorTotalCompra = valorTotalCompra + itemXpreco;
                break;
            }

            else if (controlPesquisa == 0)
            {
                printf("\n\nCodigo do item invalido ou incorreto!\n\n");
                printf("\n\nTENTE NOVAMENTE!\n\n");

                system("pause");


                break;
            }
        case 2:
            if (removItem == 1)
            {
                valorTotalCompra = valorTotalCompra - itemXprecoUltimo;
                exibeItemRemovido();
                removItem = 0;
                system("pause");
                system("cls");
                break;
            }
            else
            {
                printf("\n\n So eh permitido remover o utimo item adicionado\n O ultimo item de valor :%.2f ja foi removido\n\n");
                system("pause");
                break;
            }
        case 3:
            if (valorTotalCompra > 0.00)
            {
                formaPagamento();
                break;
            }
            else
            {
                system("cls");
                printf("\n\n Sem Valor para ser recebido \n\n");
                system("pause");
                break;
            }


            ;
        default:
            invalido();
            break;
        }
    }
    while(op!=0);
}


/*
-------------------------------------
* FUN��O MENU DE FORMA DE PAGAMENTO *WN
-------------------------------------
*/
void formaPagamento()
{
    float valorTroco = 0.00;
    float valorRecebido = 0.00;
    int op;

    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                         >>>>> FORMA PAGAMENTO <<<<<                                           *\n");
    printf("*                                                                                                               *\n");
    printf("*                                         0 - Cancelar Recebimento                                              *\n");
    printf("*                                         1 - Dinheiro                                                          *\n");
    printf("*                                         2 - Cartao Debito                                                     *\n");
    printf("*                                         3 - Cartao Credito                                                    *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

    printf("\nDigite uma opcao: ");
    scanf("%d", &op);
    system("cls");

    switch (op)
    {
    case 0:
        exibeCancelaRecebimento();
        system("pause");
        break;
    case 1:
        printf("\nDigite o valor recebido: ");
        scanf("%f", &valorRecebido);
        fflush(stdin);
        if (valorRecebido >= valorTotalCompra)
        {
            valorTroco = valorRecebido - valorTotalCompra;
            printf("\nVALOR DO TROCO: %.2f\n\n", valorTroco);
            exibeRecebidoSucesso();
            valorTotalCompra = 0.00;
            itemXpreco = 0.00;
            system("pause");
            break;
        }
        else
        {
            exibeTrocoMenor();
            system("pause");
            break;
        }
    case 2:
        exibeRecebidoSucesso();
        valorTotalCompra = 0.00;
        itemXpreco = 0.00;
        system("pause");
        break;
    case 3:
        exibeRecebidoSucesso();
        valorTotalCompra = 0.00;
        itemXpreco = 0.00;
        system("pause");
        break;
    default:
        invalido();
        break;
    }

}


/*
---------------------------------------------
* FUNCAO PARA IMPRIMIR RECEBIDO COM SUCESSO *WN
---------------------------------------------
*/
void exibeRecebidoSucesso()
{
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                          >>>>>     RECEBIDO     <<<<<                                         *\n");
    printf("*                                          >>>>>   COM  SUCESSO ! <<<<<                                         *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

}


/*
------------------------------
* FUNCAO PARA SOMAR PRODUTOS *WN
------------------------------
*/
int exibeValorTotalCompra(float exibeValorTotalCompra)
{
    float itemXpreco;
    float valorTotalCompra;
    valorTotalCompra = valorTotalCompra + itemXpreco;
    return valorTotalCompra;
}

/*
-----------------------------------------------
* FUNCAO PARA BUSCAR O PRODUTO PELO CÓDIGO *IH
-----------------------------------------------
*/


void buscarCod()
{
    importaProdutos();
    int controlPesquisa = 0;
    int op;
    Produtos *aux = inicioPro;

    do
    {
        system("cls");
        printf("*****************************************************************************************************************\n");
        printf("*                                                                                                               *\n");
        printf("*                                          >>>>> MENU BUSCA <<<<<                                               *\n");
        printf("*                                                                                                               *\n");
        printf("*                                                0 - Retornar                                                   *\n");
        printf("*                                                1 - Buscar                                                     *\n");
        printf("*                                                                                                               *\n");
        printf("*****************************************************************************************************************\n");

        printf("\nDigite uma opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        case 0:
            printf("\n\n --->Retornando<---\n\n");
            system("pause");
            system("cls");
            limpaMemoria();
            break;
        case 1:
            controlPesquisa = 0;
            printf("\nPesquisar\n");
            fflush(stdin);
            printf("\nEntre com o codigo do Produto: ");
            fgets(codigo, sizeof(codigo), stdin);
            codigo[strcspn(codigo, "\n")]='\0';

            while(aux != NULL)
            {
                if ((strcmp(codigo, aux->codigo)) == 0)
                {

                    printf("\n\n");

                    printf("Codigo: %s\nProduto: %s\nValor: %s\n\n",aux->codigo, aux->nomProduto, aux->valor);
                    controlPesquisa = 1;

                }
                aux = aux->proximoPro;

            }
            aux = inicioPro;


            if (controlPesquisa == 1)
            {
                printf("\n\n--->Busca realizada com sucesso!<---\n\n");
                system ("pause");

                break;
            }

            else if (controlPesquisa == 0)
            {
                printf("\n\nCodigo do item invalido ou incorreto !\n\n");
                printf("\n\nTENTE NOVAMENTE!\n\n");

                system("pause");


                break;

            default:
                invalido();
                break;
            }
        }
    }
    while(op!=0);

}



/*
-----------------------------------------------
* FUNCAO QUE ENTRA PARA GUIA DE CADASTRO *IH
-----------------------------------------------
*/


void cadastroFull()
{

    system("cls");
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                              >>>> CADASTRO <<<<                                               *\n");
    printf("*                                                                                                               *\n");
    printf("*                                              0 - Retornar                                                     *\n");
    printf("*                                              1 - Cadastrar                                                    *\n");
    printf("*                                              2 - Exibir todos os itens cadastrados                            *\n");
    printf("*                                              3 - Buscar item por Codigo                                       *\n");
    printf("*                                              4 - Excluir                                                      *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");



    printf("Entre com uma opcao: ");
    scanf("%d", &cadas);

    if (cadas == 0 )
    {
        printf("\n\n --->Retornando<---\n\n");
        system("pause");
    }

    else if (cadas == 1)
    {
        novoCadastro();
    }
    else if (cadas == 2)
    {
        produtosCadastrados();
    }
    else if (cadas == 3)
    {
        buscarCod();
    }
    else if (cadas == 4)
    {
        excluirCadastro();
    }
    else
    {
        printf("\n\n--->Operacao invalida!<---\n\n");
        system("pause");
    }

}// FIM CADASTROFULL


/*
-----------------------------------------------------
* FUNCAO QUE ENTRA NO MENU DE OPERAÇÕES PRINCIPAL *IH
-----------------------------------------------------
*/

void menuOpcao()
{
    system("cls");


    logo();

    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                          >>>> OPERACOES <<<<                                                  *\n");
    printf("*                                                                                                               *\n");
    printf("*     O-----                                    0 - SAIR                                             -----O     *\n");
    printf("*           |                                   1 - CADASTRO                                        |           *\n");
    printf("*           |                                   2 - CAIXA                                           |           *\n");
    printf("*            ---------------                    3 - INFORMACOES DO SISTEMA           ---------------            *\n");
    printf("*           |               |                                                       |               |           *\n");
    printf("*           |  HiPIMercado! |                                                       |  HiPIMercado! |           *\n");
    printf("*           |               |                                                       |               |           *\n");
    printf("*            ---------------                                                         ---------------            *\n");
    printf("*             O           O                                                           O           O             *\n");
    printf("*                                                                                                               *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n\n");

    printf("\nSelecione uma opcao por favor: ");
    scanf("%d", &Opcao);

}//FIM MENU OPCAO.


/*
-----------------------------------------------
* FUNCAO QUE EXIBE OS PRODUTOS CADASTRADOS *IH
-----------------------------------------------
*/

void produtosCadastrados()
{
    FILE *pont_arq;
    char texto_str[10000];


    system("cls");
    printf("\n\n");
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                       >>>>> PRODUTOS CADASTRADOS <<<<<                                        *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n");

    printf("\n\n");

    printf("Cod|Produto|Valor\n\n");

    pont_arq = fopen("estoqueProdutos.txt", "r");


    while(fgets(texto_str, 1000, pont_arq) != NULL)

        printf("%s", texto_str);

    printf("\n\n");


    if (pont_arq==NULL)
    {
        fprintf(stderr, "*****************************************************************************************************************\n");
        fprintf(stderr, "*                                                                                                               *\n");
        fprintf(stderr, "*                                               >>>>> AVISO! <<<<<                                              *\n");
        fprintf(stderr, "*                                     >>>>> SEM PRODUTOS CADASTRADOS! <<<<<                                     *\n");
        fprintf(stderr, "*                                                                                                               *\n");
        fprintf(stderr, "*****************************************************************************************************************\n\n\n");
    }


    fclose(pont_arq); //FECHANDO O ARQUIVO.

    system("pause");



} // FIM VOID PRODUTOS CADASTRADOS.


/*
---------------------------------------------------
* FUNCAO QUE INSERE UM NOVO CADASTRO DE PRODUTO *IH
---------------------------------------------------
*/

void novoCadastro()
{

    do
    {
        FILE *pont_arq;
        char texto_str[1000];//USADA PARA LER OS VALORES DE LINHA EM LINHA NO ARQUIVO TXT.


        system("cls");
        printf("*****************************************************************************************************************\n");
        printf("*                                                                                                               *\n");
        printf("*                                          >>>>> NOVO CADASTRO <<<<<                                            *\n");
        printf("*                                                                                                               *\n");
        printf("*****************************************************************************************************************\n");
        printf("\n\n");

        printf("Deseja realizar um novo cadastro? 1 - Sim / 2 - Nao: ");
        scanf("%d", &rept);

        system("cls");
        printf("*****************************************************************************************************************\n");
        printf("*                                                                                                               *\n");
        printf("*                                          >>>>> NOVO CADASTRO <<<<<                                            *\n");
        printf("*                                                                                                               *\n");
        printf("*****************************************************************************************************************\n");
        printf("\n\n");


        if (rept==1)
        {

            char cod1 = 0; //CÓDIGO DO PRODUTO, COM O ZERO FIXO.
            char cod2 = 0; //CÓDIGO DO PRODUTO, COM O ZERO FIXO.
            char cod3 = 0; //CÓDIGO DO PRODUTO PARA O CADASTRO, INICIANDO COM O VALOR UM, ATÉ O NÚMERO DE CADASTROS REALIZADO.



            FILE *file;
            file = fopen("codite.txt", "r");

            fscanf(file, "%d", &cod3); //LÊ NO ARQUIVO E GUARDA NA VARIAVEL O CODIGO QUE SERA UTILIZADO PARA O CADASTRO.

            cod3 ++;
            fclose(file);

            file = fopen("codite.txt", "w");
            fprintf(file,"%d%d%d", cod1, cod2, cod3);
            fclose(file);
            printf("\nO codigo do produto sera: %d%d%d\n\n",cod1, cod2, cod3);





            FILE *pont_arqN; //CRIA VARIAVEL PONTEIRO PARA O ARQUIVO TXT.



            pont_arqN = fopen("estoqueProdutos.txt", "a");// ABRINDO O ARQUIVO NO MODO A, QUE NÃO DEIXA SOBREESCREVER.


            if(pont_arqN == NULL)//TESTANDO SE O ARQUIVO FOI CRIADO.
            {
                printf("--->Erro na abertura do arquivo!<---");
                return 1;
            }

            printf("Produto: ");
            fflush(stdin); //LIMPAR O BUFFER DO TECLADO.
            gets(nomProduto);

            printf("Valor: ");
            scanf("%f", &valor);
            fflush(stdin);

            fprintf(pont_arqN, "%d%d%d|%s|%.2f\n",cod1, cod2, cod3, nomProduto, valor); //INSERE NO ARQUIVO TXT O CODIGO, NOME E VALOR DO PRODUTO.


            fclose(pont_arqN);

            printf("\n\n--->Dados gravados com sucesso!<---\n\n");

        }

        else if (rept==2)
        {
            printf("\n\n--->Retornando<---\n\n");
            system("pause");
        }


        else if ((rept!=1) && (rept!=2))
        {
            printf("\n\n--->Operacao invalida!<---\n\n");
            system("pause");
        }

    }
    while (rept!=2);

}//FIM NOVO CADASTRO


/*
-----------------------------------------------
* FUNCAO PARA EXCLUIR TODOS OS DADOS DO TXT *IH
-----------------------------------------------
*/

void excluirCadastro()
{
    do
    {
        system("cls");
        printf("*****************************************************************************************************************\n");
        printf("*                                                                                                               *\n");
        printf("*                                            >>>>> EXCLUIR DADOS! <<<<<                                         *\n");
        printf("*                                                                                                               *\n");
        printf("*****************************************************************************************************************\n");

        printf("\n\n");
        printf("Deseja realmente apagador todos os dados? 1 - Sim / 2 - Nao: ");
        scanf("%d", &rept);

        if (rept==1)
        {

            system("cls");
            printf("\n\n");
            printf("*****************************************************************************************************************\n");
            printf("*                                                                                                               *\n");
            printf("*                                       >>>>> DADOS EXCLUIDOS COM SUCESSO! <<<<<                                *\n");
            printf("*                                                                                                               *\n");
            printf("*****************************************************************************************************************\n");

            printf("\n\n");


            printf("\t\t\t                             oooooooooooooo                              \n");
            printf("\t\t\t                             oo          oo                              \n");
            printf("\t\t\t                         oooooooooooooooooooooo                          \n");
            printf("\t\t\t                         o  o  o  o  o  o  o  o                          \n");
            printf("\t\t\t                         o  o  o  o  o  o  o  o                          \n");
            printf("\t\t\t                         oooooooooooooooooooooo                          \n");
            printf("\t\t\t                           o                o                            \n");
            printf("\t\t\t                           o                o                            \n");
            printf("\t\t\t                           o      TODOS     o                            \n");
            printf("\t\t\t                           o       OS       o                            \n");
            printf("\t\t\t                           o      DADOS     o                            \n");
            printf("\t\t\t                           o    EXCLUIDOS!  o                            \n");
            printf("\t\t\t                           o                o                            \n");
            printf("\t\t\t                           o                o                            \n");
            printf("\t\t\t                           o                o                            \n");
            printf("\t\t\t                           o     ooooooo    o                            \n");
            printf("\t\t\t                           o     o     o    o                            \n");
            printf("\t\t\t                           oooooooooooooooooo                           \n\n\n");


            remove("estoqueProdutos.txt");//APAGA O ARQUIVO TXT DE CADASTRO.
            remove("codite.txt");//APAGA O ARQUIVO TXT DO CODIGO DO PRODUTO.
            system ("pause");

        }

        else if (rept==2)
        {
            printf("\n\n--->Retornando<---\n\n");
            system("pause");
        }

        else if ((rept!=1) && (rept!=2))
        {
            printf("\n\n--->Operacao invalida!<---\n\n");
            system("pause");
        }


    }
    while((rept!=2) && (rept!=1));

}//FIM EXCLUIR CADASTRO TXT.



/*
-----------------------------------------------
* FUNCAO DE LOGOUT PARA SAÍDA DO SISTEMA *IH
-----------------------------------------------
*/

void logout()
{
    system("cls");
    printf("\n\n");
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                                >>>>> ATE MAIS! <<<<<                                          *\n");
    printf("*                                     >>>>> O HiPIMercado agradece sua preferencia! <<<<<                       *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n\n");

    printf("\t\t\t                   O-----                            \n");
    printf("\t\t\t                         |                           \n");
    printf("\t\t\t                         |                           \n");
    printf("\t\t\t                          ---------------            \n");
    printf("\t\t\t                         |               |           \n");
    printf("\t\t\t                         |  HiPIMercado! |           \n");
    printf("\t\t\t                         |               |           \n");
    printf("\t\t\t                          ---------------            \n");
    printf("\t\t\t                           O           O             \n");

    printf("\n*****************************************************************************************************************");
    printf("\n*****************************************************************************************************************\n");
    printf("\n\t  $$$$$   $$$     $$$    $$$$$$$$   $$$$$$$    $$$$$$$$    $$$$$$$$     $$$$$$$$    $$$     $$$     ");
    printf("\n\t $$       $$$$   $$$$    $$    $$   $$    $$   $$$$$$$$    $$     $$    $$$$$$$$    $$$$   $$$$     ");
    printf("\n\t $$	  $$  $ $  $$    $$    $$   $$    $$      $$       $$     $$       $$       $$  $ $  $$      ");
    printf("\n\t  $$$$    $$   $   $$    $$$$$$$$   $$$$$$$       $$       $$$$$$$         $$       $$   $   $$     ");
    printf("\n\t     $$   $$       $$    $$    $$   $$  $$        $$       $$              $$       $$       $$     ");
    printf("\n\t     $$   $$       $$    $$    $$   $$   $$       $$       $$           $$$$$$$$    $$       $$     ");
    printf("\n\t $$$$$    $$       $$    $$    $$   $$    $$      $$       $$           $$$$$$$$    $$       $$  \n   ");

    printf("\n*****************************************************************************************************************");

    printf("\n************************************ |A MELHOR SOLUCAO PARA SEU NEGOCIO| ****************************************\n\n\n");

    system("pause");
    printf("\n\n");
    return 0;

}//FIM LOGOUT



/*
-----------------------------------------------
* FUNCAO QUE EXIBE OS INTEGRANTES DO GRUPO *IH
-----------------------------------------------
*/

void informacoesSistema()
{

    system("cls");

    FILE *pont_arq;
    char texto_str[10000];


    system("cls");
    printf("\n\n");
    printf("*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                                                                                               *\n");
    printf("*                                     >>>>> INFORMACOES DO SOFTWARE! <<<<<                                      *\n");
    printf("*                                                                                                               *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n\n");


    pont_arq = fopen("informacoes.txt", "r");


    while(fgets(texto_str, 1000, pont_arq) != NULL)

        printf("%s", texto_str);

    printf("\n\n\n\n");
    system("pause");


    system("cls");
    printf("\n*****************************************************************************************************************\n");
    printf("*                                                                                                               *\n");
    printf("*                                                                                                               *\n");
    printf("*                                     >>>>> INFORMACOES DO SOFTWARE! <<<<<                                      *\n");
    printf("*                                                                                                               *\n");
    printf("*                                                                                                               *\n");
    printf("*****************************************************************************************************************\n\n");

    printf("\t\t                          >>>>> DESENVOLVEDORES! <<<<<                                                    \n\n");

    printf("\t\t\t\t  Nome: Wagner Rodrigues Neves    RA: D794HF-3                                                          \n\n");
    printf("\t\t\t\t  Nome: Igor Henrique da Silva    RA: D8269B-0                                                          \n\n");
    printf("\t\t\t\t  Nome: Paluan Batista da Silva   RA: D78132-4                                                          \n\n");
    printf("\t\t\t\t  Nome: Marcos Roberto Lopes      RA: N3757D-3                                                          \n\n");
    printf("\t\t\t\t  Nome: Jonathas Toledo Pereira   RA: D835CB-2                                                          \n\n");

    printf("\n*****************************************************************************************************************");
    printf("\n*****************************************************************************************************************\n");
    printf("\n\t  $$$$$   $$$     $$$    $$$$$$$$   $$$$$$$    $$$$$$$$    $$$$$$$$     $$$$$$$$    $$$     $$$     ");
    printf("\n\t $$       $$$$   $$$$    $$    $$   $$    $$   $$$$$$$$    $$     $$    $$$$$$$$    $$$$   $$$$     ");
    printf("\n\t $$	  $$  $ $  $$    $$    $$   $$    $$      $$       $$     $$       $$       $$  $ $  $$      ");
    printf("\n\t  $$$$    $$   $   $$    $$$$$$$$   $$$$$$$       $$       $$$$$$$         $$       $$   $   $$     ");
    printf("\n\t     $$   $$       $$    $$    $$   $$  $$        $$       $$              $$       $$       $$     ");
    printf("\n\t     $$   $$       $$    $$    $$   $$   $$       $$       $$           $$$$$$$$    $$       $$     ");
    printf("\n\t $$$$$    $$       $$    $$    $$   $$    $$      $$       $$           $$$$$$$$    $$       $$  \n   ");

    printf("\n*****************************************************************************************************************");

    printf("\n************************************ |A MELHOR SOLUCAO PARA SEU NEGOCIO| ****************************************\n\n");

    printf("\n*********************************************** |Versao 1.0| ****************************************************\n");

    printf("\n\n");

    system("pause");


}

/*
-----------------------------------------------
* FUNCAO QUE EXIBE A FUNÇÃO DE VENDAS *WN
-----------------------------------------------
*/

/*
void vendas ()
{
    int op;
    do{
    system("cls");
    int op;


    importaProdutos();

    exibeMenuPrincipal();
    }while(op!=0);

}
*/

/*
-----------------------------------------------
* INT MAIN *IH
-----------------------------------------------
*/


int main(void)
{
    system ( "Color F0" );//COR DO CONSOLE.

    system("mode con cols=168 lines=60"); //TAMANHO DA TELA --> USAR NO INICIO E SEMPRE ANTES DO DO WHILE.
    system("title HiPIMercado"); // TITULO QUE APARECE NO CONSOLE.

    do
    {
        menuOpcao();

        if (Opcao==0)
        {
            logout();
        }

        else if (Opcao==1)
        {
            do
            {
                cadastroFull();
            }
            while(cadas!=0);
        }

        else if (Opcao==2)
        {
            //vendas();
                importaProdutos(); exibeMenuPrincipal();

        }

        else if (Opcao==3)
        {
            informacoesSistema();
        }


        else
        {
            printf("\n\n--->Operacao invalida!<---\n\n");
            system("pause");
        }


    }
    while (Opcao != 0);

    return 0;

}//FIM MAIN.
