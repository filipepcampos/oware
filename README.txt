Controlos:
'A', 'B', 'C', 'D', 'E', 'F' ou 'a', 'b', 'c', 'd', 'e', 'f' -> Escolher jogada

"end" (any case accepted) - Termina o jogo (útil no caso de loops infinitos), os de cada lado do tabuleiro
são atribuídos ao jogador respetivo.

Decisões de design:
O jogo é guardado num std::array<int, 12> cujos indíces correspondem às respetivas posições:
| 11 | 10 |  9 |  8 |  7 |  6 |
|  0 |  1 |  2 |  3 |  4 |  5 |
Esta organização permite simplificar as funções de "sow" e "capture" pois estas seguem o sentido anti-horário,
ao custo de funções de print e input mais complexas.

Todas as strings constantes são guardadas num ficheiro "Text", isto permite à partilha de constantes pelos
diversos ficheiros (principalmente códigos ANSI). Também facilita a tradução do jogo para outras linguagens com
facilidade.

Se ocorrer EOF durante a leitura de input o utilizador receberá uma mensagem a informar que ocorreu um erro
de IO e o programa irá terminar.

Existem 3 modos de jogo:
1 - Single player: O jogador joga contra um bot que escolhe a jogada que lhe dará mais sementes, é também usada uma
condição random no caso de haver mais que uma jogada com o número máximo de sementes.

2 - Local two player: Dois jogadores no mesmo computador.

3 - Network two player: Dois jogadores em computadores diferentes ou no mesmo computador em processos separados.
Neste modo um dos jogadores será "host", e aparecerá o seu ip no ecrã através do qual outro jogador se pode conectar.
- O IP é obtido através de uma conecção ao Google DNS (8.8.8.8)
- Se um processo no computador for "host" e outro processo tentar ser "host" o segundo jogador ligar-se-á ao primeiro
como client.
- Se um terceiro jogador tentar-se conectar será recusado.