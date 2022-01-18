# TP1 - Introduction au C++


## Exercice 1 - Compilation et exécution

1. Quels sont les avantages et désavantages d'un langage dit "*compilé*" (C, C++, Pascal) ou "*semi-compilé*" (Java) comparé à un langage dit "*interpreté*" (Python, PHP, Javascript, etc) ?

- Un langage dit "compilé" ou semi-compilé" sera plus rapide et facile à exécuter qu'un langage interprété.
- La gestion de la mémoire est plus précise (utilisation de pointeurs/références).
- Il sera en revanche non portable et devra être recompilé pour chaque machine, ou si les dépendances changent. 

2. Quelle est la différence entre une erreur de compilation et une erreur d'exécution ? (à quel moment se produisent-elles ? dans quelles circonstances ? comment les identifier ? comment les corriger ? ...)

- Une erreur de compilation se produit lorsqu'on tente de compiler le code. Celà signifie qu'il y a une erreur lexicale, syntaxique ou sémantique entre autre qui rend le code non traduisible en exécutable. En général, elles sont plus simples à corriger car le compilateur détecte où se trouve le problème. On peut les attraper avec un static_assert(false).
- Une erreur d'exécution se produit lorsqu'on exécute le programme (en appelant son exécutable). Le code fonctionne, mais ne produit pas ce que l'on veut. Cela peut être dû à un problème de mémoire, une exception (par exemple une division par 0 etc). On peut les attraper avec un assert(false).

3. Que signifie en pratique l'expression "*undefined behavior*" (UB) ? Peut-on compiler un programme contenant du code classifié UB par le standard ? Si oui, que peut-il se produire au moment de son exécution ?

Littéralement "comportement indéfini", s'obtient quand on tente d'allouer à une variable une valeur non fixée par le standard. Celà ne produit pas d'erreur mais une valeur absurde à la place. Celà généralise également les erreurs de compilation ou d'exécution, mais on en parle en général pour définir ces valeurs absurdes.

## Exercice 2 - Primitives et initialisation

En C++, il existe plein de syntaxes différentes pour initialiser une variable de type primitif (int, char, bool, ...) :

```cpp
int v;       // pas d'initialisation            -> valeur indéfinie
int v = 2;   // initialisation avec '= value'   -> value
int v {};    // initialisation avec '{}'        -> tous les bits à 0
int v {};    // initialisation avec '{}'        -> tous les bits à 0
int v { 2 }; // initialisation avec '{ value }' -> value
int v(2);    // initialisation avec '(value)'   -> value

```

1. Parmi les lignes suivantes, lesquelles déclenchent des erreurs de compilation ? Quelles sont ces erreurs et comment les corriger ?\
Mêmes questions en ajoutant l'option `-Werror` à la compilation.\
Vous pouvez utiliser [CompilerExplorer](https://www.godbolt.org/z/rPPoro) pour tester la compilation de petits snippets de code.

```cpp
short       s0;
const short s1; // s1 initialisé avec une valeur indéfinie en tant que variable constante. 

const int i1 = 2;

bool b2{false};
bool b3{i1}; // b3 initialisé avec la valeur d'un booléen de valeur 2. Conversion int -> bool 32 bits -> 1 bits.
bool b4;

unsigned       u5{0x10};
unsigned short us6 = -10;
unsigned long  ul7{b3 + u5 + us6};

char c8{"a"}; // On tente de convertir un string en char 64 bits -> 8 bits.
char c9 = -10;

double       d10{i1};
double&      d11{d10};
double&      d12; // On ne peut pas créer de références sur une valeur non initialisée.
const double d13{.0f};

int        i14 = i1;
int&       i15 = i1; // On ne peut pas faire de référence sur une variable constante.
int&       i16 = b2; // On ne peut pas faire de références d'entier non constant valeur gacuhe sur un entier valeur droite.
const int& i17{i14};
```

2. Pouvez-vous donner la valeur de `s0` ? De `ul7` ?

s0 est indéfini. ul7 également car il contient b3 qui lui-même est indéfini.


## Exercice 3 - Les fonctions et leurs paramètres

1. Remplacez les `XX` par les bons types, de manière à ce que le programme compile et affiche `42`.

```cpp
#include <iostream>

int add(const int a, const int b) {
  return a + b;
}

void add_to(int& a, int b) {
  a += b;
}

void another_add_to(int* a, int b) {
  *a += b;
}

int main() {
  const int x{10};
  int y = add(x, x);
  another_add_to(&y, y);
  add_to(y, 2);
  std::cout << y << std::endl;

  return 0;
}
```

2. En C++, vous pouvez passer vos paramètres par valeur, par référence et par référence constante.
Quelles sont les différences entre ces différentes méthodes de passage ?
Dans quels contextes est-il préférable de passer par valeur ? Par référence ? Et par référence constante ?

- On préférera passer par valeur lorsque l'on veut utiliser les valeurs sans modifier directement les addresses des variables concernées. On sera davantage interessé par la valeur elle même et non pas par la variable qui la stocke. add utilise simplement les valeurs de a et b et renvoie la somme dans un autre pan de la mémoire. C'est du passage par copies.

- On préférera passer par références si on veut modifier plusieurs valeurs dans la fonction. L'idée est de modifir la référence directement si on le désire. L'avantage est que l'on peut modifier autant de valeurs que l'on vet sans avoir à retourner quoi que ce soit obligatoirement. add_to va ici prendre la référence de a et modifier directement la valeur de a en lui ajoutant la valeur de b. Ici, on modifie directement la valeur contenue dans la référence a.

- On préférera passer par références constantes si on n'a pas l'intention de changer le paramètre mais que l'on ne veut pas pour autant copier l'argument en question (par exemple un tableau). Ici, ce n'est pas ce que nous avons fait.



3. Modifiez les signatures des fonctions suivantes de manière à ce que le passage de paramètres soit le plus efficace et sécurisé possible.
Vous pouvez vous aidez des commentaires pour comprendre comment les fonctions utilisent leurs paramètres.
```cpp
// Return the number of occurrences of 'a' found in string 's'.
int count_a_occurrences(const std::string s);

// Update function of a rendering program.
// - dt (delta time) is read by the function to know the time elapsed since the last frame.
// - errors is a string filled by the function to indicate what errors have occured.
void update_loop(const float dt, std::string& errors_out);

// Return whether all numbers in 'values' are positive.
// If there are negative values in it, fill the array 'negative_indices_out' with the indices
// of these values and set its size in 'negative_count_out'.
// ex: auto res = are_all_positive({ 1, -2, 3, -4 }, negative_indices, negative_count);
//    -> res is false, since not all values are positive
//    -> negative_indices contains { 1, 3 } because values[1] = -2 and values[3] = -4
//    -> negative_count is 2
bool are_all_positives(const std::vector<int>& values, int negative_indices_out[], size_t& negative_count_out);

// Concatenate 'str1' and 'str2' and return the result.
// The input parameters are not modified by the function.
std::string concatenate(const char* str1, const char* str2);
```


## Exercice 4 - `std::string` et `std::vector`

1. Ecrivez un programme qui utilise `std::cin` pour lire une variable de type `std::string`, puis calcule et affiche pour chaque lettre minuscule ('a', 'b', ..., 'z') le nombre des fois où elle apparaît.\
Le comptage des lettres se fera dans une fonction `count_lower` prenant une chaîne de caractères en paramètre et renvoyant un `std::vector<unsigned int>`. La première case du tableau contiendra le nombre d'occurences de 'a', la seconde de 'b', etc.\
Vous afficherez ce tableau dans une seconde fonction `display_lower_occ`.\
Essayez d'utiliser les signatures qui rendront votre programme le plus efficace possible.

2. Modifiez le programme pour que l'utilisateur puisse entrer plusieurs chaînes de caractères, jusqu'à ce qu'il entre la chaîne "QUIT".\
Vous afficherez en plus des occurrences la concaténation de toutes les chaînes de caractères renseignées par l'utilisateur.


## Exercice 5 - Traducteur malade

Dans la vie, on se retrouve souvent face à du code tout pourri qu'il faut débugguer. Afin de vous préparer psychologiquement aux tourments de votre futur métier de programmeur, vous allez devoir corriger le code du programme que vous trouverez dans le dossier `tp-01` du dépôt https://github.com/Laefy/CPP_Learning_Code/.

---

Ce programme consiste en un traducteur, censé s'utiliser comme suit :
```b
# Ajoute une nouvelle traduction au dictionnaire dict.txt (il est créé s'il n'existe pas).
./translator -d path/to/dict.txt -a chat cat

# Utilise le dictionnaire dict.txt pour traduire la phrase "le chat est beau"
./translator -d path/to/dict.txt le chat est beau
```

Voici le format attendu pour le fichier dict.txt :
```b
bonjour hello
cheval horse
tu you
```
---

1. Pour commencer, essayez de faire en sorte que le programme compile.\
Un indice : si seulement on pouvait bannir les chaînes de caractères de type char*.

2. Une fois que le programme compile, essayez de le lancer, afin de constater que le programme est bourré de bug.\
Placez un breakpoint sur la première ligne du `main`, lancez le programme en mode debug et itérez d'instruction en instruction, tout en inspectant le contenu des variables.\
Cela vous permettra d'identifier d'où viennent les problèmes pour réussir à les corriger.

> Dans VSCode, vous pouvez placer des breakpoints avec F9, lancer un programme en mode debug via F5 (il faut modifier le fichier launch.json pour passer des arguments au programme), exécuter l'instruction courante avec F10, entrer dans un appel de fonction avec F11 et en sortir avec Shift+F11. Afin de voir le contenu des variables, ouvrez le panneau d'exécution (`View > Run`) et regardez dans la section `Variables`.

> Voici la liste des types de problèmes que trouverez dans le programme :
>- passage par valeur au lieu de référence,
>- mauvais usage de `std::vector`,
>- condition inversée ou au mauvais endroit.

3. Si vous parvenez à corriger tous les bugs, vous pouvez faire une dernière passe sur le programme afin de remplacer les passages par valeur coûteux par des passages par const-ref, et ajouter les `const` sur toutes les variables qui ne sont pas modifiées après leur initialisation.   

---

Céline Noël, Stéphane Vialette, Mathias Weller  
C++ Master 1    
2020 - 2021
