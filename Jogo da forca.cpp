// Bibliotecas usadas para o desenvolvimento do jogo
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <string>
#include <time.h> // Biblioteca usada para gerar n�meros aleat�rios.
using namespace std;
// ----------------


// Fun��o para limpar a tela do terminal
void limpaTela(){
	system("CLS");
}
// -----------------------

// Fun��o que retorna palavras aleat�rias.
string retornaPalavraAleatoria() {
	
	// Vetor com palavras dispon�veis.
	string palavras[9] = {"manga", "abacaxi", "morango","abacate","laranja","cadeira","paralelepipedo","otorrinolaringologista","geladeira"};
	
	int indiceAleatorio = rand() % 9; // Indice gerado no intervalo {0,1...,9}.
	
	return palavras[indiceAleatorio];
	
}

// Retorna a palavra aleat�ria ou inserida pelo usu�rio escondida (EX: _ _ _ _ _). 
string retornaPalavraComMascara(string palavra, int tamanhoDaPalavra){
	
	int cont = 0;
	string palavraComMascara;
	
	while(cont < tamanhoDaPalavra){
		palavraComMascara += "_";
		cont ++;
	}
	
	return palavraComMascara;
}

// Fun��o que exibe os status de tamanho da palavra, tentativas e letras j� arriscadas.
void exibeStatus(string palavraComMascara, int tamanhoDaPalavra, int tentativasRestantes, string letrasJaArriscadas, string mensagem) {
	cout << mensagem;
	cout << "\nPalavra: " << palavraComMascara << "(Tamanho: " << tamanhoDaPalavra << ")";
	cout <<"\n\n" << "Tentativas restantes: " << tentativasRestantes;
	
	// Exibe as letras arriscadas pelo jogador.
	int cont;
	cout << "\nLetras arriscadas: [";
	for(cont = 0; cont < letrasJaArriscadas.size(); cont++){
		cout << letrasJaArriscadas[cont]  << ",";			
	}
	cout << "]";
}


int jogar(int numeroDeJogadores){
	
	// Palavra a ser adivinhada.
	string palavra;
	
	if(numeroDeJogadores == 1){
	
		palavra = retornaPalavraAleatoria();
	
	}else{
		cout << "\nDigite a palavra a ser advinhada: ";
		cin >> palavra;
		
	}
	
	
	
	int tamanhoDaPalavra = palavra.size();	// Tamanho da palavra.
	
	// Palavra mascarada
	string palavraComMascara = retornaPalavraComMascara(palavra, tamanhoDaPalavra);
	
	
	// Variaveis 
	int tentativas = 0, maximoTentativas = 10; 				// N�mero de tentativas e erros.
	int cont = 0;							 				// Auxiliar para la�os de repeti��o.
	int reiniciar;											// Escolha caso o jogador queira jogar novamente.
	char letra;												// Letra arriscada pelo jogador.
	string letrasJaArriscadas;								// Acumula as tentativas do jogador.
	string palavraToda;										// armazena a palavra completa que o jogador digitar.
	string mensagem = "Bem vindo ao jogo!";					// Feedback do jogador.
	bool jaDigitouLetra = false, acertouLetra = false;		// Auxiliar para saber se a letra ja foi digitada.
	
	
	while(palavra != palavraComMascara && maximoTentativas - tentativas > 0){
		
		limpaTela();
		
		// Exibe o status atual do jogo.
		exibeStatus(palavraComMascara, tamanhoDaPalavra, maximoTentativas - tentativas, letrasJaArriscadas, mensagem);
		
		cout << "\nDigite uma letra (Ou digite 1 para arriscar a palavra): ";	// L� um palpite.
		cin >> letra;
		
		if (letra == '1'){
			cout << "Qual � a palavra? ";
			cin >> palavraToda;
			if(palavraToda == palavra){
				palavraComMascara = palavraToda;
				mensagem = "\nParab�ns, voc� acertou a palavra\n\n";
				
			}else{
				limpaTela();
				maximoTentativas = 0;	// Caso o usu�rio arrisque uma palavra inteira e erre, zera suas tentativas e ele perde automaticamente.
				cout << "\nVoc� errou a palavra\n\n";
			}
		}
		
		// Percorre as letras j� arriscadas.
		for(cont = 0; cont < tentativas; cont ++){
			
			// Se encontrar a letra.
			if(letrasJaArriscadas[cont] == tolower(letra)){
				mensagem = "Voc� j� digitou essa letra!";
				
				//indica uma vari�vel booleana.
				jaDigitouLetra = true;
			}
		}
		
		if(jaDigitouLetra == false){
			
			letrasJaArriscadas += tolower(letra);
		
			for(cont = 0; cont < tamanhoDaPalavra; cont++){
			
				if(palavra[cont] == tolower(letra)){
					
					palavraComMascara[cont] = palavra[cont];
					
					acertouLetra = true;
				}
			}
			
			if(acertouLetra == false){
			
				mensagem = "Voc� errou uma letra!";
				
			}else{
				
				mensagem = "Voc� acertou uma letra!";
			}
		
			tentativas ++; // Aumenta uma tentativa realizada.	
		}
			
			// Reinicia as vari�veis auxiliares.
			jaDigitouLetra = false;
			acertouLetra = false;
			
	}
				
			if(palavra == palavraComMascara){
				limpaTela();
				cout << "Parab�ns, voc� venceu\n\n";
				cout << "Deseja reiniciar o jogo?\n" << "1 - SIM" << "\n2 - N�O" <<"\n";
				cin >> reiniciar;
				return reiniciar;
			
			}else{
				cout << "0 tentativas restantes. Poxa, mais sorte da pr�xima vez! :(\n\n";
				cout << "Deseja reiniciar o jogo?\n" << "1 - SIM" << "\n2 - N�O" <<"\n";
				cin >> reiniciar;
				return reiniciar;
			}
	
}



// Inicio da fun��o que mostra o Menu Inicial para o jogador.
void menuInicial(){
	
	int opcao = 0;	// Vari�veis
	
	// Enquanto o jogador n�o digita uma op��o v�lida, mostra o menu novamente.
	while(opcao < 1 || opcao > 4){
		
		limpaTela(); // Chamando a fun��o que limpa a tela.
		
		cout << "JOGO DA FORCA\n";
		cout << "1 - Jogar sozinho\n";
		cout << "2 - Jogar em dupla\n";
		cout << "3 - Sobre o jogo\n";
		cout << "4 - Sair\n";
		cout << "Escolha uma op�ao e tecle ENTER: ";
		cin >> opcao; // Armazena a op��o escolhida pelo jogador.
		
		// Faz algo de acordo com a op��o escolhida pelo jogador.
		switch(opcao){
			case 1:
				if (jogar(1) ==  1){
					
					menuInicial();
				}else{
					limpaTela();
					cout << "\n At� a pr�xima :)\n";
				}
				break;
				
			case 2:
				if (jogar(2) ==  1){
					
					menuInicial();
				}else{
					limpaTela();
					cout << "\n At� a pr�xima :)\n";
				}
				break;
				
			case 3:
				limpaTela();
				int voltar;
				cout << "\nINFORMA��ES DO JOGO\n" <<"\nJogo desenvolvido em 07/07/2024 a t�tulo de estudo.\n\n";
				cout << "Desenvolvedor: Eduardo Graminho Marques.\nContato (41) 9 91960198\n";
				cout << "\n1 - Voltar" << "\n2 - sair\n";
				cin >> voltar;
					
					if(voltar == 1){
						menuInicial();
					}else{
						limpaTela();
						cout << "\n At� a pr�xima :)\n";
					}
					break;
			
			
			case 4:
				limpaTela();
				cout << "\n At� a pr�xima :)\n";
				break;
				
		}
	}
}
// FIM da fun��o que mostra o Menu Inicial para o jogador.


int main() {
	setlocale(LC_ALL,""); // Permite letras com  acentos serem exibidas no terminal.
	
	// Para gerar n�meros realmente aleat�rios (USADO EM CONJUNTO COM A BIBLIOTECA TIME.H).
	srand(( unsigned) time(NULL));
	

	menuInicial(); // Chama a fun��o que mostra o menu para o jogador.


//	system("pause");
	return 0;
}
