##Tron-Many: Proiectarea algoritmilor - Proiect 2013##

**Nume echipa:** Shift-Delete  
**Membri:** Manta Paul-Cristian (323CB), Popescu Gabriel-Cosmin (323CB),
Scarlat Tiberiu (323CB), Velea Cosmin (323CB) 

**HackerRank:** [hackerrank.com/ShiftDelete][1]  
**Gmail:** tron.shift.delete@gmail.com

###Etapa II###

Tag: `stage-ii-submission`

Pentru aceasta etapa am implementat un algoritm ce foloseste echilibrul 
Nash pentru a gasi mutarea care minimizeaza sansele de a pierde meciul. 
Pentru a evalua starea hartii (si a decide care jucator este in avantaj), 
am aproximat cat de raspandita este zona accesibila fiecarui jucator 
in urmatorul fel (pseudocod):

    area       := getProximalArea(player) 
    rowSpread  := rowVariance(area)
    colSpread  := colVariance(area)
    areaSpread := rowSpread * colSpread  

Functiile `rowVariance` si `colVariance` calculeaza  varianta (din 
statistica) a sufrafetei date, dupa cele doua axe. Daca  toate celulele 
se afla pe o singura linie sau coloana, atunci `rowSpread`, respectiv 
`colSpread`, va fi zero deci si produsul celor doua va fi zero.

Algoritmul ce foloseste echilibrul Nash cauta cu o adancime foarte mica 
(din motive de eficienta), ceea ce inseamna ca nu va avea o performanta 
foarte buna cand jucatorul este prea departe. Pentru a combate asta, am 
implementat si algoritmul A\*, pentru a ne putea apropria de adversar 
cand suntem prea departe. Euristica folosita impreuna cu A\* este 
distanta Manhattan.

**Solutie:** [hackerrank.com/.../submissions/game/635151][35]  
**Meciuri stage2bot:** [a][36] - [b][37] - [c][38] - [d][39] - [e][40] - 
[f][41] - [g][42] - [h][43] - [i][44] - [j][45] - [k][46] - [l][47] - 
[m][48] - [n][49] - [o][50] - [p][51]  


###Etapa I###

Tag: `stage-i-submission`

Pentru etapa I am implementat un AI foarte rudimentar: tot ce face este 
sa se duca tot timpul in directia celui mai lung coridor pe care il poate 
vedea la un moment dat. Am cazut de comun acord sa abordam o solutie cat 
mai simpla posibil in aceasta prima etapa pentru a ne putea incadra in 
timp.

Insa codul pe care l-am scris este facut in asa fel incat sa poata fi 
extins si facut mai complex in etapele urmatoare; spre exemplu, clasa 
`GameWorld`, pe care am facut-o in asa fel incat sa ne fie mai usor in 
viitor sa implementam un algoritm de tip minimax.

Nota: Codul trimis pentru aceasta etapa nu este de pe branch-ul 
principal, asa ca unule parti ale clasei `GameWorld` nu sunt cele mai 
recente pe care le avem pe repository-ul de pe GitHub.

**Solutie:** [hackerrank.com/.../submissions/game/624187][2]  
**Meciuri RandomBot:** [a][3] - [b][4] - [c][5] - [d][6] - [e][7] - 
[f][8] - [g][9] - [h][10] - [i][11] - [j][12] - [k][13] - [l][14] - 
[m][15] - [n][16] - [o][17] - [p][18]  
**Meciuri explorer:** [a][19] - [b][20] - [c][21] - [d][22] - [e][23] - 
[f][24] - [g][25] - [h][26] - [i][27] - [j][28] - [k][29] - [l][30] - 
[m][31] - [n][32] - [o][33] - [p][34] 

 [1]: https://www.hackerrank.com/ShiftDelete
 [2]: https://www.hackerrank.com/contests/bucharest-tron/submissions/game/624187
 [3]: https://www.hackerrank.com/showgame/2134081
 [4]: https://www.hackerrank.com/showgame/2134056
 [5]: https://www.hackerrank.com/showgame/2134061
 [6]: https://www.hackerrank.com/showgame/2134068
 [7]: https://www.hackerrank.com/showgame/2134058
 [8]: https://www.hackerrank.com/showgame/2134068
 [9]: https://www.hackerrank.com/showgame/2134063
 [10]: https://www.hackerrank.com/showgame/2134064
 [11]: https://www.hackerrank.com/showgame/2134071
 [12]: https://www.hackerrank.com/showgame/2134072
 [13]: https://www.hackerrank.com/showgame/2134075
 [14]: https://www.hackerrank.com/showgame/2134077
 [15]: https://www.hackerrank.com/showgame/2134080
 [16]: https://www.hackerrank.com/showgame/2134084
 [17]: https://www.hackerrank.com/showgame/2134086
 [18]: https://www.hackerrank.com/showgame/2134087
 [19]: https://www.hackerrank.com/showgame/2134107
 [20]: https://www.hackerrank.com/showgame/2134107
 [21]: https://www.hackerrank.com/showgame/2134111
 [22]: https://www.hackerrank.com/showgame/2134113
 [23]: https://www.hackerrank.com/showgame/2134115
 [24]: https://www.hackerrank.com/showgame/2134117
 [25]: https://www.hackerrank.com/showgame/2134119
 [26]: https://www.hackerrank.com/showgame/2134127
 [27]: https://www.hackerrank.com/showgame/2134129
 [28]: https://www.hackerrank.com/showgame/2134131
 [29]: https://www.hackerrank.com/showgame/2134133
 [30]: https://www.hackerrank.com/showgame/2134135
 [31]: https://www.hackerrank.com/showgame/2134138
 [32]: https://www.hackerrank.com/showgame/2134140
 [33]: https://www.hackerrank.com/showgame/2134143
 [34]: https://www.hackerrank.com/showgame/2134145
 [35]: https://www.hackerrank.com/contests/bucharest-tron/submissions/game/635151
 [36]: https://www.hackerrank.com/showgame/2301194
 [37]: https://www.hackerrank.com/showgame/2301195
 [38]: https://www.hackerrank.com/showgame/2301196
 [39]: https://www.hackerrank.com/showgame/2301197
 [40]: https://www.hackerrank.com/showgame/2301198
 [41]: https://www.hackerrank.com/showgame/2301199
 [42]: https://www.hackerrank.com/showgame/2301200
 [43]: https://www.hackerrank.com/showgame/2301201
 [44]: https://www.hackerrank.com/showgame/2301202
 [45]: https://www.hackerrank.com/showgame/2301203
 [46]: https://www.hackerrank.com/showgame/2301204
 [47]: https://www.hackerrank.com/showgame/2301205
 [48]: https://www.hackerrank.com/showgame/2301206
 [49]: https://www.hackerrank.com/showgame/2301207
 [50]: https://www.hackerrank.com/showgame/2301208
 [51]: https://www.hackerrank.com/showgame/2301209
