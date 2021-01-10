- "wizytówka" studentów
Michał Sobieraj, Michał Łątkowski 300208

****************************************************************************************
- krótka specyfikacja problemu (albo przynajmniej tytuł problemu)
Sortowanie kolorowych kulek na pochylni za pomocą dźwigu przenoszącego trzy na raz

****************************************************************************************
-informacja o możliwych poleceniach aktywacji programu (opcje, parametry, ...)
Tryby działania programu:
1) crane -m1 <in.txt >out.txt
W tym trybie in.txt i out.txt to odpowiednio plik, z którego pobieramy dane dot. kulek (ciąg literek R, G i B) oraz plik, do którego zapisujemy ilość ruchów wykonanych przez nasz algorytm. in.txt musi być podane, ale out.txt może nie być, wtedy program wypisze dane (czas, jaki zajęło wykonanie algorytmu i ilość ruchów) na konsolę.

2) crane -m2 -n X -d B G R >out.txt
W tym trybie X to ilość kulek a B, G, R to ilości kulek odpowiednich kolorów (program generuje ciąg kulek proporcjonalnie i go miesza). B+G+R musi równać się X. W przypadku niepodania B, G i R (czyli polecenia w formie crane -m2 -n X >out.txt) algorytm wygeneruje losowy ciąg kulek o długości X.
Do out.txt, jeśli zostanie podane, algorytm wypisuje czas jaki zajęło wykonanie algorytmu i ilość ruchów

3) crane -m3 -n A -k B -step C -r D
Ten tryb pozwala na generację pełnego ciągu testowego. A to początkowa ilość kulek, B to ilość problemów, C to krok, D to ilość instancji problemu (np. dla A=500, B=3, C=500, D=10 program analizuje problemy o rozmiarze 500, 1000 i 1500, dla każdego rozmiaru problemu generując 10 instancji problemu). Program zapisuje wyniki testów w pliku output_table.txt

4) crane -m4 -n A -p B >out.txt
Ten tryb pozwala na generację takiego ciągu kulek o rozmiarze A, że istnieje prawdopodobieństwo B (dopuszczalne wartości od 0 do 1), że każda (prócz oczywiście pierwszej) kulka będzie taka sama, jak kulka poprzednia. W przeciwnym wypadku kulka będzie wygenerowana z równą szansą na każdy z trzech kolorów. Do out.txt, jeśli zostanie podane, algorytm wypisuje czas jaki zajęło wykonanie algorytmu i ilość ruchów

****************************************************************************************
-opis konwencji dotyczących danych wejściowych i prezentacji wyników
Dane wejściowe, jeśli użytkownik wybierze opcję wymagającą ich podania, to ciąg B, G i R odpowiadającym kolorom kulek (niebieski, zielony i czerwony).
Wyniki są zapisywane do plików .txt lub wyświetlane na ekranie.

-krótki opis metody rozwiązania, zastosowanych algorytmów i struktur danych
TODO

****************************************************************************************
-informacje o funkcjonalnej dekompozycji programu na moduły źródłowe - nagłówkowe i
implementacyjne ("przewodnik" po plikach źródłowych)
Program składa się z plików: Clock.cpp, Generator.cpp, InterfaceHandler.cpp, AlgorithmRunner.cpp i main.cpp (wszystkie prócz main mają swoje pliki nagłówkowe .hpp).
-Clock implementuje zegar, udostępnia możliwość rozpoczęcia mierzenia czasu, zakończenia mierzenia czasu i wyświetlenia czasu, który upłynął pomiędzy wywołaniem metody rozpoczęcia i zakończenia pomiaru
-Generator pozwala na cztery typy generacji: całkowicie losową, sparametryzowaną (tzn. użytkownik podaje ile ma być kulek o danym kolorze), probabilistyczną (tzn. użytkownik podaje z jakim prawdopodobieństwem każda kulka prócz pierwszej ma być tego samego koloru co poprzednia) i z pliku (używane w przypadku wybrania trybu 1).
-InterfaceHandler zajmuje się wczytaniem argumentów podanych przed użyciem, sprawdzeniem jej poprawności, pobraniem od użytkownika informacji o wybranym algorytmie i uruchomienie odpowiedniego.
-AlgorithmRunner to klasa przechowująca wszystkie metody odpowiadające za sortowanie ciągu kulek i informowanie użytkownika o wynikach sortowania
****************************************************************************************
-inne informacje dodatkowe o szczególnych decyzjach projektowych (np. ograniczenia dotyczące
rozmiaru problemu, charakterystyki generatorów danych testowych, specjalne konwencje w
alokacji pamięci dynamicznej, wymagania dotyczące typów parametryzujących szablony,
konwencje związane z obsługą sytuacji wyjątkowych, itp.)
Dynamiczna alokacja nie występuje jawnie, bo używamy struktur danych z STL. Generatory danych testowych korzystają z biblioteki <random> (seedowane są czasem w momencie uruchomienia programu). W razie wystąpienia sytuacji wyjątkowej, użytkownik jest informowany o tym fakcie poprzez odpowiedni komunikat wyświetlony na konsoli (lub zapisany w pliku wyjściowym, jeśli użytkownik przekierował standardowe wejście poleceniem shellowym).
