<h1>Länkar</h1>
http://www.interactivecode.com/programming-coding-1/implementing-quadratic-sieve-3805/
http://xvid.se/~xun/001692.html
http://www.nada.kth.se/~joel/qs_lecture.pdf
http://www.math.uiuc.edu/~landquis/quadsieve.pdf
http://www.mersennewiki.org/index.php/P-1_Factorization_Method


<h2>Pollard's rho algoritm</h2>
Om talet som går in i algoritmen är ett primtal kommer det returneras som en faktor.
Funktionen vi använder för att titta om ett tal är ett primtal kan även säga om talet
<em>sannolikt</em> är ett primtal.

<del>Vi kan alltså inte testa större tal för att den sannolikhetsfunktionen blir fel</del>

Det är även möjligt att vår vektor som innehåller faktorerna genererar fel, då den endast
innehåller unsigned long ints, så faktorerna kan bli större än det som får plats i den

Det visade sig vara vektorn, det ser vi nu när vi ignorerar de faktorer som inte får plats i vår vektor

<h3>Förbättringar</h3>
<ul>
<li><del>Ändra på hur många iterationer primtalsfunktioen kör för att kolla om något är ett primtal</del></li>
<li>Om vi inte får fram ett "fail" från pollards algoritm så kan vi testa ändra på funktionen</li>
<li>För att öka hastigheten kan man testa cachea faktoriseringar</li>
<li>Få std::vector<mpz_t> att fungera</li>
</ul>

<h1>GMP</h1>

Det visade sig att jag använt c-versione av gmp, tydligen finns det en c++ version också, då man använder mpz_class 
istället för mpz_t.

mpz_t går tex inte att stoppa in i en vektor, det går fint med mpz_class. 

Jag vet INTE hur man gör alla operationer som man kan göra på em mpz_t på em mpz_class, det verkar nästan som
att man måste konvertera den till en mpz_t varje gång, vilket känns otympligt

För tillfället så använder jag mpz_t överallt förutom när jag stoppar in faktorerna i vektorn för utskrift, då 
gör jag om dem till mpz_class. Jag tror det fungerar tillräckligt bra, då det som max finns 100 faktorer på ett 100
bitars tal. Så maximalt kommer vi kasta om mpz_t till mpz_class 50*100=5000 gånger, det känns inte som så mycket overhead

<h1>Quadratic Sieve</h1>

<h2>Liten kom-ihåg-lista.</h2>

<ul>
<li>Fixa så att basen innehåller -1 och därmed klarar negativa tal.</li>
</ul>
