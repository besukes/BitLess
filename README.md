## Overview

BitLess é um simples compressor de dados que utiliza algoritmos como o de Shannon-Fano para reduzir o tamanho de ficheiros.<br>
Este repositório foi criado após aprender o algoritmo Shannon-Fano de compressão de dados , para aprender melhor como funcionam algoritmos de compressão na prática , como um tipo de inicialização na matéria.
<br>
Este projeto foi iniciado no dia **26 de setembro de 2026** por um estudante de Engenharia Informática na UMinho.

## Compilação

Para compilar basta utilizar o comando

```
    make compressor 
```

E para abrir o programa basta correr o comando 

```
    ./compressor (path)
```

Onde **path** seria o caminho para o ficheiro que quer comprimir.
O utilizador pode incluir vários paths e todos eles serão comprimidos.
Após execução do programa ele díra quanto tempo demorou a comprimir e será gerado um ficheiro do mesmo tipo , na mesma pasta do comprimido , com o nome do ficheiro seguido por "_zip".
<br>
Um exemplo prático seria um ficheiro calculos.txt que ficaria no final , na mesma pasta onde se encontra calculos.txt , agora com o nome calculos_zip.txt .
<br>
O programa também dirá no final a percentagem de compressão que conseguiu fazer , o rendimento desta compressão , noutras palavras.

## Outros comandos

O utilizador pode também usar os comandos:

Para apagar a pasta build e o executável ***compressor***.

```
    make clean
```

Para apagar os ficheiros ***(%_zip.txt)*** da pasta tests.

```
    make rmt
```



