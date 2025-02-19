# Atividade U4C8 - Embarcatech

**Autor:** Reinan Lopes Argolo

## Descrição
Este projeto demonstra a integração de periféricos com o Raspberry Pi Pico:  
- Inicialização e controle de LEDs (com PWM), botões e ADC.  
- Uso do joystick para ajustar a intensidade dos LEDs e movimentar um quadrado em um display OLED.  
- Configuração e renderização no display OLED (SSD1306) via comunicação I2C.  
- Diagramas de conexão e fluxos de dados presentes no arquivo `diagram.json`.

## Funcionalidades
- Inicialização de LEDs e botões utilizando GPIO.
- Controle do brilho dos LEDs por PWM com leitura de valores analógicos via ADC.
- Renderização de gráficos (quadrado e bordas) no display OLED.
- Processamento de entradas do joystick para alterar o estado dos LEDs e posição do quadrado.
- Debounce e controle manual via botão.

## Instruções
- Configure e compile o projeto para o Raspberry Pi Pico.
- Garanta o correto cabeamento conforme o diagrama.
- Ajuste os parâmetros (sensibilidade, thresholds) se necessário para sua aplicação.

## Vídeo Demonstrativo
<!-- Espaço reservado para o vídeo da atividade - insira o link ou embed do vídeo aqui -->

## Estrutura de Código
- `src/init.h` e `src/init.c`: Inicialização de periféricos e funções auxiliares.
- `src/functions.h` e `src/functions.c`: Processamento de dados do joystick e renderização no display.
- `inc/ssd1306.h` e `inc/ssd1306.c`: Funções específicas para o controle do display OLED.
- `diagram.json`: Diagrama de conexões da atividade.
- `U4C8.c`: Arquivo principal que integra todas as funcionalidades.

<!-- ...other project files and setup instructions... -->
