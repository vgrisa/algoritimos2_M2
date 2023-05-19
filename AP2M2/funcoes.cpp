#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15

struct Jogador
{
    string nome;
    int passos;
    char ultimoMovimento;

    void escolheNome()
    {
        cout << "Escolha seu nome: ";
        cin >> nome;
    }

    void imprimeNumeroPassos(int &passos)
    {
        cout << "numero de passos: " << passos << endl;
    }
};

struct Mapa
{
    void leMapas(char m[50][50], int &x, int &y, string escolha, int &linhas, int &colunas)
    {
        string nomeArquivo;
        if (escolha.length() > 1)
        {
            nomeArquivo = escolha + ".txt";
        }
        else
        {
            nomeArquivo = "mapa" + escolha + ".txt";
        }
        cout << nomeArquivo;

        int a;
        fstream arquivo;
        arquivo.open(nomeArquivo);
        if (arquivo.is_open())
        {
            arquivo >> linhas >> colunas;
            arquivo >> x >> y;

            for (int i = 0; i < linhas; i++)
            {
                for (int j = 0; j < colunas; j++)
                {
                    arquivo >> a;
                    m[i][j] = a;
                }
            }

            arquivo.close();
        }
        else
        {
            cout << "O arquivo nao pode ser aberto";
            arquivo.close();
        }
    }

    int menuEscolheMapa(int &x, int &y, char m[50][50], int &numeroCaixas, int &linhas, int &colunas)
    {
        string escolha;

        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                m[i][j] = 0;
            }
        }

        system("cls");
        cout << "Escolha seu mapa:\n"
             << endl;

        cout << "[1] - MicroBanIv : 1\n";
        cout << "[2] - Aruba 5 : 1\n";
        cout << "[3] - TBox 2 : 1\n";
        cout << "Ou digite o nome do arquivo\n"
             << endl;

        cout << "Digite o mapa que voce quer jogar: ";
        cin >> escolha;

        leMapas(m, x, y, escolha, linhas, colunas);
        numeroCaixas = 0;
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (m[i][j] == 4 || m[i][j] == 2)
                {
                    numeroCaixas++;
                }
            }
        }
        if (escolha == "1" || escolha == "mapa1")
        {
            return 1;
        }
        return 0;
    }

    void imprimeTrocado(char m[10][15])
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 15; j++)
            {

                switch (m[i][j])
                {
                case 0:
                    cor_texto(7, 0);
                    cout << " ";
                    break; // caminho
                case 1:
                    cor_texto(11, 0);
                    cout << char(219);
                    break; // parede
                case 2:
                    cor_texto(6, 0);
                    cout << char(176);
                    break; // caixa
                case 3:
                    cor_texto(10, 0);
                    cout << char(169);
                    break; // posicao final
                case 4:
                    cor_texto(4, 0);
                    cout << char(178);
                    break; // caixa na posicao final
                           // default: cout<<"-"; //erro
                }          // fim switch
                cor_texto(7, 0);
            }
            cout << "\n";
        }
    }

    void cor_texto(int fonte, int fundo = 0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(fonte | fundo << 4));
    }

    void imprimeMapaPersonagem(char m[50][50], int x, int y, int linhas, int colunas)
    {
        /// Imprime o jogo: mapa e personagem.
        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (i == x && j == y)
                {
                    cor_texto(15, 0);
                    cout << char(2); // personagem
                }
                else
                {
                    switch (m[i][j])
                    {
                    case 0:
                        cor_texto(7, 0);
                        cout << " "; // caminho
                        break;
                    case 1:
                        cor_texto(11, 0);
                        cout << char(219); // parede
                        break;
                    case 2:
                        cor_texto(6, 0);
                        cout << char(176); // caixa
                        break;
                    case 3:
                        cor_texto(10, 0);
                        cout << char(169); // posicao final
                        break;
                    case 4:
                        cor_texto(4, 0);
                        cout << char(178); // caixa na posicao final
                        break;
                    } // fim switch
                    cor_texto(7, 0);
                }
            }
            cout << "\n";
        } // fim for mapa
    }
};

struct Movimentos
{
    void apagaMovimentos()
    {
        ofstream arquivo;
        arquivo.open("movimentos.txt");
        if (arquivo.is_open())
        {
            arquivo << " ";
            arquivo.close();
        }
        else
        {
            cout << "O arquivo nao pode ser aberto";
        }
    }

    void registroMovimentos(char ultimoMovimento)
    {

        ofstream arquivo;
        arquivo.open("movimentos.txt", std::ios::app);
        if (arquivo.is_open())
        {
            arquivo << ultimoMovimento << " ";

            arquivo.close();
        }
        else
        {
            cout << "O arquivo não pode ser aberto";
        }
    }

    void executaMovimentos(char tecla, char m[50][50], int &x, int &y, bool &sair, int &passos, char &ultimoMovimento)
    {
        if (_kbhit())
        {
            tecla = getch();
            movimento(tecla, m, x, y, sair, passos, ultimoMovimento);
        } // fim do if
    }

    void movimento(char tecla, char m[50][50], int &x, int &y, bool &sair, int &passos, char &ultimoMovimento)
    {
        int modificadorX, modificadorY;
        switch (tecla)
        {
        case 72:
        case 'w': /// cima
            modificadorX = -1;
            modificadorY = 0;
            break;
        case 80:
        case 's': /// baixo
            modificadorX = 1;
            modificadorY = 0;
            break;
        case 75:
        case 'a': /// esquerda
            modificadorX = 0;
            modificadorY = -1;
            break;
        case 77:
        case 'd': /// direita
            modificadorX = 0;
            modificadorY = 1;
            break;
        case 'l': /// sair
            modificadorX = 0;
            modificadorY = 0;
            sair = true;
            break;
        }

        switch (m[x + modificadorX][y + modificadorY])
        {
        case 0:
            if (modificadorX != 0)
            {
                x += modificadorX;
                passos++;
                if (modificadorX == 1)
                {
                    ultimoMovimento = 's';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'w';
                    registroMovimentos(ultimoMovimento);
                }
            }
            if (modificadorY != 0)
            {
                y += modificadorY;
                passos++;
                if (modificadorY == 1)
                {
                    ultimoMovimento = 'd';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'a';
                    registroMovimentos(ultimoMovimento);
                }
            }
            break;

        case 2:
            switch (m[x + modificadorX * 2][y + modificadorY * 2]) // acima da caixa
            {
            case 0:
                m[x + modificadorX][y + modificadorY] = 0;
                m[x + modificadorX * 2][y + modificadorY * 2] = 2;
                if (modificadorX != 0)
                {
                    x += modificadorX;
                    passos++;
                    if (modificadorX == 1)
                    {
                        ultimoMovimento = 's';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'w';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                if (modificadorY != 0)
                {
                    y += modificadorY;
                    passos++;
                    if (modificadorY == 1)
                    {
                        ultimoMovimento = 'd';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'a';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                break;

            case 3:
                m[x + modificadorX][y + modificadorY] = 0;
                m[x + modificadorX * 2][y + modificadorY * 2] = 4;
                if (modificadorX != 0)
                {
                    x += modificadorX;
                    passos++;
                    if (modificadorX == 1)
                    {
                        ultimoMovimento = 's';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'w';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                if (modificadorY != 0)
                {
                    y += modificadorY;
                    passos++;
                    if (modificadorY == 1)
                    {
                        ultimoMovimento = 'd';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'a';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                break;
            }
            break;

        case 3:
            if (modificadorX != 0)
            {
                x += modificadorX;
                passos++;
                if (modificadorX == 1)
                {
                    ultimoMovimento = 's';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'w';
                    registroMovimentos(ultimoMovimento);
                }
            }
            if (modificadorY != 0)
            {
                y += modificadorY;
                passos++;
                if (modificadorY == 1)
                {
                    ultimoMovimento = 'd';
                    registroMovimentos(ultimoMovimento);
                }
                else
                {
                    ultimoMovimento = 'a';
                    registroMovimentos(ultimoMovimento);
                }
            }
            break;

        case 4:
            switch (m[x + modificadorX * 2][y + modificadorY * 2])
            {
            case 0:
                m[x + modificadorX][y + modificadorY] = 3;
                m[x + modificadorX * 2][y + modificadorY * 2] = 2;
                if (modificadorX != 0)
                {
                    x += modificadorX;
                    passos++;
                    if (modificadorX == 1)
                    {
                        ultimoMovimento = 's';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'w';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                if (modificadorY != 0)
                {
                    y += modificadorY;
                    passos++;
                    if (modificadorY == 1)
                    {
                        ultimoMovimento = 'd';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'a';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                break;

            case 3:
                m[x + modificadorX][y + modificadorY] = 3;
                m[x + modificadorX * 2][y + modificadorY * 2] = 4;
                if (modificadorX != 0)
                {
                    x += modificadorX;
                    passos++;
                    if (modificadorX == 1)
                    {
                        ultimoMovimento = 's';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'w';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                if (modificadorY != 0)
                {
                    y += modificadorY;
                    passos++;
                    if (modificadorY == 1)
                    {
                        ultimoMovimento = 'd';
                        registroMovimentos(ultimoMovimento);
                    }
                    else
                    {
                        ultimoMovimento = 'a';
                        registroMovimentos(ultimoMovimento);
                    }
                }
                break;
            }
            break;
        }
    }

    bool retornaGanhou(int &numeroCaixas, char m[50][50], int linhas, int colunas)
    {
        int caixasCorretas = 0;

        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                if (m[i][j] == 4)
                {
                    caixasCorretas++;
                }
            }
        }

        if (caixasCorretas == numeroCaixas)
        {
            return true;
        }
        return false;
    }

    void conferePosicoesRanking(string nome, int passos, string nomeRanking[3], int passosRanking[3])
    {

        for (int i = 0; i < 3; i++)
        {
            if (passosRanking[i] > passos)
            {
                if (i == 0 || i == 1)
                {
                    nomeRanking[i + 1] = nomeRanking[i];
                    passosRanking[i + 1] = passosRanking[i];
                    nomeRanking[i] = nome;
                    passosRanking[i] = passos;
                }
                else
                {
                    nomeRanking[i] = nome;
                    passosRanking[i] = passos;
                }
                break;
            }
        }
    }

    void mostraRanking()
    {
        int i = 0, passosRanking[3];
        string filename, nomeRanking[3];
        ifstream arquivo;

        filename = "ranking.txt";

        arquivo.open(filename);
        if (arquivo.is_open())
        {
            while (i < 3 && arquivo >> nomeRanking[i] >> passosRanking[i])
            {
                i++;
            }
            arquivo.close();
        }
        else
        {
            cout << "O arquivo não pode ser aberto";
        }

        cout << "RANKING:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << " - " << nomeRanking[i] << ": " << passosRanking[i] << " passos" << endl;
        }
        cout << endl;
    }

    void leRanking(string nomeRanking[3], int passosRanking[3], int mapinha)
    {
        int i = 0;
        string filename;
        ifstream arquivo;

        filename = "ranking.txt";
        arquivo.open(filename);
        if (arquivo.is_open())
        {
            while (i < 3 && arquivo >> nomeRanking[i] >> passosRanking[i])
            {
                i++;
            }
            arquivo.close();
        }
        else
        {
            cout << "O arquivo não pode ser aberto";
        }
    }

    void resetaRanking()
    {
        string resetNomeRanking[3] = {"bot_Invencivel", "bot_Invencivel", "bot_Invencivel"};
        int resetPassosRanking[3] = {9999, 9999, 9999};
        int i = 0;
        ofstream arquivo;
        arquivo.open("ranking.txt");
        if (arquivo.is_open())
        {

            while (i < 3)
            {
                arquivo << resetNomeRanking[i] << " " << resetPassosRanking[i] << endl;
                i++;
            }
            arquivo.close();
        }
        else
        {
            cout << "O arquivo não pode ser aberto";
        }
    }

    void escreveRanking(string nome, int passos, int mapinha)
    {
        if (mapinha == 1)
        {
            string nomeRanking[3];
            int passosRanking[3];
            int i = 0;
            leRanking(nomeRanking, passosRanking, mapinha);
            conferePosicoesRanking(nome, passos, nomeRanking, passosRanking);
            ofstream arquivo;
            arquivo.open("ranking.txt");
            if (arquivo.is_open())
            {

                while (i < 3)
                {
                    arquivo << nomeRanking[i] << " " << passosRanking[i] << endl;
                    i++;
                }
                arquivo.close();
            }
            else
            {
                cout << "O arquivo não pode ser aberto";
            }
        }
    }
};

struct Menu
{
    Movimentos movimento;
    Mapa mapa;
    void reposicionaCursor()
    {
        // IN CIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        short int CX = 0, CY = 0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN CIO DA TELA
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void naoPisca()
    {
        /// ALERTA: N O MODIFICAR O TRECHO DE C DIGO, A SEGUIR.
        // INICIO: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        // FIM: COMANDOS PARA QUE O CURSOR N O FIQUE PISCANDO NA TELA
    }
    void functionMenu()
    {
        Jogador player;
        int escolhaMenu = 0, numeroCaixas = 0, jogar = 1, mapinha = 1, y = 4, x = 1, linhas = 0, colunas = 0;
        bool ganhou = false, sair = false;
        char m[50][50], tecla;
        string nomeArquivo;

        player.ultimoMovimento;

        do
        {
            system("cls");
            cout << "Bem vindo a Sokoban Master Ultra 3000" << endl;
            cout << "[1] - Jogar" << endl;
            cout << "[2] - Sobre" << endl;
            cout << "[3] - Ranking" << endl;
            cout << "[4] - Reset Ranking" << endl;
            cout << "[5] - Sair" << endl;
            cout << "Digite sua escolha: ";
            cin >> escolhaMenu;

            switch (escolhaMenu)
            {
            case 1:
                system("cls");

                if (sair)
                {
                    cout << "[1] - Novo jogo" << endl;
                    cout << "[2] - Continuar" << endl;
                    cout << "Digite sua escolha: ";
                    cin >> jogar;
                }

                if (jogar == 1)
                {
                    movimento.apagaMovimentos();
                    naoPisca();
                    sair = false;
                    ganhou = false;
                    player.escolheNome(); // chamada de metodo struct
                    player.passos = 0;
                    mapinha = mapa.menuEscolheMapa(x, y, m, numeroCaixas, linhas, colunas);
                    system("cls");
                }
                else
                {
                    naoPisca();
                    system("cls");
                    sair = false;
                    ganhou = false;
                    jogar = 1;
                }

                while (!sair && !ganhou)
                {
                    /// Posiciona a escrita no início do console
                    reposicionaCursor();
                    cout << "para sair presione [L]" << endl;
                    mapa.imprimeMapaPersonagem(m, x, y, linhas, colunas);
                    player.imprimeNumeroPassos(player.passos);
                    movimento.executaMovimentos(tecla, m, x, y, sair, player.passos, player.ultimoMovimento);
                    ganhou = movimento.retornaGanhou(numeroCaixas, m, linhas, colunas);
                    if (ganhou == true)
                    {

                        system("cls");
                        mapa.imprimeMapaPersonagem(m, x, y, linhas, colunas);
                        player.imprimeNumeroPassos(player.passos);
                        movimento.escreveRanking(player.nome, player.passos, mapinha);
                        cout << "Parabens, " << player.nome << " voce ganhou o joguinho... " << endl;
                        cout << "Pressione qualquer tecla pra voltar ao menu" << endl;
                        system("pause");
                        sair = false;
                    }
                }
                break;
            case 2:
                escolhaMenu = 0;
                system("cls");
                cout << "Sokoban eh um jogo de movimentacao de caixas onde o objetivo eh \n"
                        "alocar as caixas no local certo usando estrategia e logica.\n\n"
                        "Esse jogo foi desenvolvido pelos alunos do curso de Ciencias da computacao\n"
                        "da universidade do vale do Itajai(UNIVALI), para materia de algoritmos e programacao 2\n"
                        "lecionada pelo professor Thiago Felski.\n"
                        "Alunos: Vinicius Grisa, Gabriel Turman, Marco Antonio Martins Akerman\n"
                        "Data: Marco 2022"
                     << endl;
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                movimento.mostraRanking();
                system("pause");
                break;
            case 4:
                movimento.resetaRanking();
                break;

            case 5:

                system("cls");
                cout << "Obrigado por jogar Sokoban Mater Ultra 3000" << endl;
                break;
            }
            if (escolhaMenu == 5)
                break;

        } while (true);
    }
};