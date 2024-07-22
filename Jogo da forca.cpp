// Bibliotecas usadas para o desenvolvimento do jogo
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <locale.h>
#include <string>
#include <time.h> // Biblioteca usada para gerar números aleatórios.
using namespace std;
// ----------------


// Função para limpar a tela do terminal
void limpaTela(){
	system("CLS");
}
// -----------------------


string retornaPalavraAleatoria() {
	// Vetor com palavras disponíveis.
	string palavras[3] = {"manga", "abacaxi", "morango"};
	
	int indiceAleatorio = rand() % 3; // Indice gerado no intervalo {0,1,2}.
	
	return palavras[indiceAleatorio];
	
}

string retornaPalavraComMascara(string palavra, int tamanhoDaPalavra){
	
	int cont = 0;
	string palavraComMascara;
	
	while(cont < tamanhoDaPalavra){
		palavraComMascara += "_";
		cont ++;
	}
	
	return palavraComMascara;
}

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
	int tentativas = 0, maximoTentativas = 10; 				// Número de tentativas e erros.
	int cont = 0;							 				// Auxiliar para laços de repetição.
	int reiniciar;											// Escolha caso o jogador queira jogar novamente;
	char letra;												// Letra arriscada pelo jogador.
	string letrasJaArriscadas;								// Acumula as tentativas do jogador.
	string palavraToda;										// armazena a palavra completa que o jogador digitar.
	string mensagem = "Bem vindo ao jogo!";					// Feedback do jogador
	bool jaDigitouLetra = false, acertouLetra = false;		// Auxiliar para saber se a letra ja foi digitada.
	
	
	while(palavra != palavraComMascara && maximoTentativas - tentativas > 0){
		
		limpaTela();
		
		// Exibe o status atual do jogo.
		exibeStatus(palavraComMascara, tamanhoDaPalavra, maximoTentativas - tentativas, letrasJaArriscadas, mensagem);
		
		cout << "\nDigite uma letra (Ou digite 1 para arriscar a palavra): ";	// Lê um palpite
		cin >> letra;
		
		if (letra == '1'){
			cout << "Qual é a palavra? ";
			cin >> palavraToda;
			if(palavraToda == palavra){
				palavraComMascara = palavraToda;
				mensagem = "\nParabéns, você acertou a palavra\n\n";
				
			}else{
				limpaTela();
				maximoTentativas = 0;
				cout << "\nVocê errou a palavra\n\n";
			}
		}
		
		// Percorre as letras já arriscadas.
		for(cont = 0; cont < tentativas; cont ++){
			
			// Se encontrar a letra.
			if(letrasJaArriscadas[cont] == tolower(letra)){
				mensagem = "Você já digitou essa letra!";
				
				//indica uma variável booleana.
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
			
				mensagem = "Você errou uma letra!";
				
			}else{
				
				mensagem = "Você acertou uma letra!";
			}
		
			tentativas ++; // Aumenta uma tentativa realizada	
		}
			
			// Reinicia auxiliares
			jaDigitouLetra = false;
			acertouLetra = false;
			
	}
				
			if(palavra == palavraComMascara){
				limpaTela();
				cout << "Parabéns, você venceu\n\n";
				cout << "Deseja reiniciar o jogo?\n" << "1 - SIM" << "\n2 - NÃO" <<"\n";
				cin >> reiniciar;
				return reiniciar;
			
			}else{
				cout << "0 tentativas restantes. Poxa, mais sorte da próxima vez! :(\n\n";
				cout << "Deseja reiniciar o jogo?\n" << "1 - SIM" << "\n2 - NÃO" <<"\n";
				cin >> reiniciar;
				return reiniciar;
			}
	
}



// Inicio da função que mostra o Menu Inicial para o jogador.
void menuInicial(){
	
	int opcao = 0;	// Variáveis
	
	// Enquanto o jogador não digita uma opção válida, mostra o menu novamente.
	while(opcao < 1 || opcao > 4){
		
		limpaTela(); // Chamando a função que limpa a tela.
		
		cout << "JOGO DA FORCA\n";
		cout << "1 - Jogar sozinho\n";
		cout << "2 - Jogar em dupla\n";
		cout << "3 - Sobre\n";
		cout << "4 - Sair\n";
		cout << "Escolha uma opçao e tecle ENTER: ";
		cin >> opcao; // Armazena a opção escolhida pelo jogador.
		
		// Faz algo de acordo com a opção escolhida pelo jogador.
		switch(opcao){
			case 1:
				if (jogar(1) ==  1){
					
					menuInicial();
				}else{
					limpaTela();
					cout << "\n Até a próxima :)\n";
				}
				break;
				
			case 2:
				if (jogar(2) ==  1){
					
					menuInicial();
				}else{
					limpaTela();
					cout << "\n Até a próxima :)\n";
				}
				break;
				
			case 3:
				limpaTela();
				int voltar;
				cout << "\nINFORMAÇÕES DO JOGO\n" <<"\nJogo desenvolvido em 07/07/2024 a título de estudo.\n";
				cout << "\n1 - Voltar" << "\n2 - sair\n";
				cin >> voltar;
					
					if(voltar == 1){
						menuInicial();
					}else{
						limpaTela();
						cout << "\n Até a próxima :)\n";
					}
					break;
			
			
			case 4:
				limpaTela();
				cout << "\n Até a próxima :)\n";
				break;
				
		}
	}
}
// FIM da função que mostra o Menu Inicial para o jogador.

void reiniciaJogo(){
	menuInicial();
}

int main() {
	setlocale(LC_ALL,""); // Permite letras com  acentos serem exibidas no terminal.
	
	// Para gerar números realmente aleatórios (USADO EM CONJUNTO COM A BIBLIOTECA TIME.H).
	srand(( unsigned) time(NULL));
	

	menuInicial(); // Chama a função que mostra o menu para o jogador.


//	system("pause");
	return 0;
}
