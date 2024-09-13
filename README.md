# App Object Oriented Programming Journalism

*******************************************************

### *IMPORTANT*
*This project was developed by me during my time at university and was created using online resources and domain-specific books as sources of inspiration. The goal of this project was to explore and learn through practical examples, combining various information and techniques found in these resources to bring it to completion.*

*Acest proiect a fost realizat de mine în timpul facultății și a fost creat folosind resurse de pe internet și cărți de specialitate drept surse de inspirație. Scopul acestui proiect a fost să explorez și să învăț prin intermediul unor exemple practice, combinând diverse informații și tehnici găsite în aceste resurse pentru a-l aduce la bun sfârșit.*

*******************************************************

## Overview | Prezentare Generală

In this project, I developed an application that models various aspects of journalism using object-oriented programming in C++. The main focus of my project is the management and processing of information related to news, reporters, and other media team members (operators, editors, sound technicians).
I created several classes to represent key entities in journalistic activities:

1. **The `Stire` Class** – I designed this class to model a news item, with attributes such as subject, location, budget, and received ratings. It includes functionality for reading and writing news items to files and managing their ratings.
2. **The `Reporter` Class** – In this class, I described a journalist, including attributes like name, experience, region, and the number of news stories they are responsible for. I also implemented methods for team management and salary calculation.
3. **The `Operator` and `Editor` Classes** – I created these classes to model other staff involved in the production of news stories, each with specific responsibilities. These classes are similar to `Reporter`, but with functionalities tailored to each role.
4. **The `IFile` Interface** – I defined this interface for handling binary files, ensuring a consistent way of managing data.

Through this project, I aimed to build an application that efficiently handles news and employee information, including functionalities for saving and loading data from files, as well as processing ratings and salary data.

*******************************************************

În cadrul acestui proiect, am implementat o aplicație care modelează diferite aspecte din domeniul jurnalismului, utilizând programarea orientată pe obiecte în C++. Tema centrală a proiectului meu este gestionarea și prelucrarea informațiilor legate de știri, reporteri și alți membri ai echipelor media (operatori, editori, sunetiști).
Am creat mai multe clase care reprezintă entități cheie din activitatea jurnalistică:

1. **Clasa `Stire`** – Am realizat această clasă pentru a modela o știre, cu atribute precum subiectul, locația, bugetul și ratingurile primite. Aceasta include funcționalități pentru citirea și scrierea știrilor în fișiere și gestionarea ratingurilor.
2. **Clasa `Reporter`** – În această clasă am descris un jurnalist, cu atribute precum numele, experiența, județul în care activează și numărul de știri pentru care este responsabil. De asemenea, am implementat metode pentru gestionarea echipei și calculul salariului.
3. **Clasa `Operator`** și **Clasa `Editor`** – Am creat aceste clase pentru a modela alți angajați implicați în producția știrilor, fiecare având atribuții specifice. Aceste clase sunt similare cu `Reporter`, dar cu funcționalități adaptate fiecărei poziții.
4. **Interfața `IFile`** – Am definit această interfață pentru gestionarea fișierelor binare, asigurând un mod uniform de manipulare a datelor.

Prin acest proiect, am urmărit să construiesc o aplicație care să permită manipularea eficientă a informațiilor legate de știri și angajați, inclusiv funcționalități de salvare și încărcare a datelor din fișiere, precum și prelucrarea datelor de rating și salarizare.

---
