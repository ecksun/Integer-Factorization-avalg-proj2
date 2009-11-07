<h2>Pollard's rho algoritm</h2>
Om talet som går in i algoritmen är ett primtal kommer det returneras som en faktor.
Funktionen vi använder för att titta om ett tal är ett primtal kan även säga om talet
<em>sannolikt</em> är ett primtal.

Vi kan alltså inte testa större tal för att den sannolikhetsfunktionen blir fel

Det är även möjligt att vår vektor som innehåller faktorerna genererar fel, då den endast
innehåller unsigned long ints, så faktorerna kan bli större än det som får plats i den

<h3>Förbättringar</h3>
<ul>
<li>Ändra på hur många iterationer primtalsfunktioen kör för att kolla om något är ett primtal</li>
<li>Om vi inte får fram ett "fail" från pollards algoritm så kan vi testa ändra på funktionen</li>
<li>För att öka hastigheten kan man testa cachea faktoriseringar</li>
<li>Få std::vector<mpz_t> att fungera</li>
</ul>


