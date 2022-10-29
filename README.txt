Acerca del programa:

ProductorConsumidor.cpp contiene una versión del problema productor-consumidor, en este
programa se utilizan semáforos como solución para cumplir la exclusión mutua. 
Esta versión del problema cuenta con algunos requisitos especificos los cuales son:
    . Existe un solo productor y un solo consumidor
    . El programa debe terminar al presionar la teclas Esc.
    . El buffer es de 25 espacios y es circular.
    . El producto es un número aleatorio entre 1 y 100;
    . Solo puede haber un proceso utilizando el buffer.
    . El consumidor quitara los elementos en orden.
    . El productor generara los elementos en orden.
    . El prodcutor o consumidor no pueden tratar de producir o consumir en un espacio en
      buffer que o bien contenga productos o que no tenga productos almacenados.
    . Al entrar en buffer podrán producir/consumir de forma finita (1 a 5), este numero 
      cambia cada vez que se despierta al proceso. 
    . En pantalla debe aparecer en todo momento la información referente al estado actual del 
      productor o del consumidor.
    . Se muestra el estado del buffer cada que se duerme un proceso y al finalizar el
      programa presionando la tecla Esc.

Requisitos del sistema para compilar:
Para poder correr este programa se necesita un sistema operativo windows de 64bits
y tener instalado la versión para 64 bits de g++. 

Notas:
  . El 0 dentro del buffer indica una posición vacía dentro del mismo. 
  . La función sleep dentro de los procesos de producir y consumir sirven para poder realizar las 
    impresiones de pantalla en orden. 
    
