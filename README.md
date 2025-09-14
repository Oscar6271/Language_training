# Instruktioner
## Starta programmet med:

./a.out <i>filnamn list språk/clear clear</i>

<i>filnamn</i> byts ut mot sökvägen för filen med orden och dess översättningar i. Filen måste vara en .txt fil men .txt ska inte skrivas ut.

<i>list</i> är ett frivilligt argument som kan skrivas för att skriva ut alla orden och dess översättningar från den valda filen

<i>språk/clear</i> byts ut med det språk man vill skriva i om inget språk anges blir det språket som översättningen står i som default

Programmet kommer som default att kunna rensa terminalen vill man inte ha den funktionaliten behöver man skriva som sista argument "no_clear"

## Format för filer
Filerna skriv enligt formatet:<br>
<i>ord</i> : översättning<br>
.<br>
.<br>
.<br>
Instruktioner<br>
Meddelande när användaren ska rätta sina fel<br>

<i>ord</i> ska skrivas språket du kan <br>
<i>översättning</i> ska skrivas på det språk du vill lära dig

På de sista 2 raderna kan man skriva egna instruktioner och meddelande för när användaren ska göra om sina fel. <br>
Om inget skrivs är blir instruktionen: "Skriv översättningen för ordet som skrivs ut"<br>
Och meddelandet: "Träna på dom ord du hade fel på"

Det är viktigt att det finns mellanrum runt om (:)-tecknet, programmet kommer att fixa till mellanrummen själv vilket kan skapa fel om mellanrummen inte finns