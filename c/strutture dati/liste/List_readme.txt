Le liste costituiscono una struttura dati logicamente strutturata come un array, 
cioe' una sequenza di elementi dello stesso tipo. 

A differenza dell'array, lo spazio per gli elementi viene allocato dinamicamente 
quando vi e' necessita' di aggiungere l'elemento stesso, ed analogamente, 
tale spazio viene liberato quando viene cancellato un elemento. 

Gli spazi in memoria degli elementi non sono contigui, per questo motivo 
vi e' la necessita' di collegare esplicitamente un elemento al successivo. 

Nelle liste ``semplicemente concatenate'' ogni nodo 
contiene il link al successivo. 
Se ogni singolo nodo contiene anche il link al precedente, 
allora si parla di liste doppiamente concatenate.

----------------------------------------------------------------------------------------

Una pila (STACK) e' una struttura dati basata sul modello LIFO 
(Last In, First Out).

Le operazioni definite sulla struttura stack sono sostanzialmente due: 

- push(..) poni un dato sul top dello stack. 
- pop(..) preleva  il dato dal top dello stack.

----------------------------------------------------------------------------------------------

Una coda e' una struttura dati che segue il modello 
FIFO (First In First Out). Il primo ad entrare 
e' il primo ad essere servito. 

In una coda le operazioni di inserimento vengono fatte sempre alla 
fine di questa, ovvero in coda (tail). 

Invece gli elementi si rimuovo dalla testa (head). 

La coda si puo' implementare facilmente con una lista concatenata con collegamenti 
semplici oppure con una ``array circolare''.


E' possibile implementare una coda mediante array gestito in modo ``circolare''. 
Si usano due indici, HEAD e TAIL. 

Sia Q l'array e d il dato da inserire nell'array. Con un array 
di n elementi sara' possibile mantenere una coda ``circolare'' 
di n-1 elementi. 

Inizialmente HEAD=TAIL=0. 

Coda vuota: HEAD==TAIL
Coda piena: HEAD==(TAIL+1)%n