<link rel="stylesheet" type='text/css' href="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/devicon.min.css" />

# Vinheria Agnello - Sistema de Monitoramento

Este projeto consiste em um sistema de monitoramento desenvolvido para a Vinheria Agnello. O sistema
tem como objetivo garantir as condições ideais de armazenamento para os vinhos, monitorando a
luminosidade do ambiente. Caso tal parâmetro esteja fora doslimites aceitáveis, o sistema aciona
alarmes visuais e sonoros para alertar os responsáveis sobre a necessidade de intervenção.

## Tecnologias Utilizadas
<div>
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cplusplus/cplusplus-original.svg" height="50" />
<img src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/arduino/arduino-original-wordmark.svg" height="50"/>
</div>
          
## Dependências do Projeto

Para reproduzir este projeto, você precisará dos seguintes componentes:

- Arduino Uno R3 (ou outro modelo compatível)
- Sensor de luminosidade (LDR)
- LEDs (verde, amarelo e vermelho)
- Buzzer
- Resistores - 3*220Ω, 1*4.20KΩ e 1*10KΩ (para limitação de corrente dos LEDs e do sensor de luminosidade e para o display)
- Display LCD 16x2
- Sensor de temperatura
- potenciômetro (Utilizado como substituito ao sensor de umidade)
- Jumpers (cabos para conexão dos componentes)
- Protoboard

## Execução

1. Monte os componentes conforme o esquema de conexões indicado no arquivo "img/Circuit.png".

2. Faça o download do código fornecido (index.ino).

3. Conecte a placa Arduino ao computador via cabo USB e configure a porta serial a ser utilizada.

4. Faça upload do código fonte para a placa Arduino.

5. Abra o monitor serial da IDE do Arduino para visualizar as mensagens de depuração (opcional).

6. Observe o comportamento do sistema de monitoramento perante as alterações dos níveis de 
luminosidade, temperatura e umidade nos sensores.

7. A cada parametro fora de padrão serão retornados alarmes, sendo visuais através dos LED's e
display LCD e sonoro via Buzzer.

## Esquema de Conexões

Certifique-se de conectar os componentes corretamente de acordo com o esquema acima para garantir o
funcionamento adequado do sistema de monitoramento.

## Código
1. Definições de Pinagem: Os pinos do Arduino são definidos para cada componente utilizado no projeto.
2. Definições de Limites: São estabelecidos os limites de luminosidade, temperatura e umidade para monitoramento.
3. Variáveis Globais: São declaradas as variáveis necessárias para armazenar as leituras dos sensores.
4. Setup(): Inicializa os pinos e o display LCD, além de iniciar a comunicação serial.
5. Loop():
  Realiza a leitura dos sensores.
  Calcula a média das últimas leituras de temperatura e umidade.
  Atualiza o display LCD a cada 5 segundos.
  Verifica se os valores lidos estão dentro dos limites definidos e controla os LEDs e o buzzer de acordo.
  Realiza a saída de depuração via comunicação serial.
6. ReadSensors(): Realiza a leitura dos sensores de luminosidade, temperatura e umidade.
7. UpdateDisplay(): Responsável por atualizar o conteúdo do display LCD.

## Observações
1. Este projeto foi desenvolvido para monitorar as condições climáticas em uma vinheria, garantindo 
que os vinhos recebam a quantidade ideal de luz, temperatura e umidade para se manterem consumiveis 
e garantindo alta qualidade.

2. Certifique-se de ajustar os parâmetros do código de acordo com as necessidades específicas do
seu projeto.

## Autor(es)

Este projeto foi desenvolvido por:
- Gabriel Machado Lacerda                RM:556714  
- João Pedro Signor Avelar               RM:558375
- Roger Cardoso Ferreira                 RM:557230
- Vinicius Augusto Siqueira Gonçalves    RM:557065
- TURMA:1ESPW
