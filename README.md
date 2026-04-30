# Solo Test (a. k. a. Peg Solitaire) Solver

[EN] This repository contains a C++ implementation of the classical game **Solo Test** solver, developed to demonstrate proficiency in **C++** and **Object-Oriented Programming (OOP)**. Moreover, it includes containerization and automated build systems as well.

This project was originally developed as an academic coursework for the **BLG 223E - Data Structures** at **Istanbul Technical University (ITU)** in 2024 - 25 Academic Year Summer Term; however, it has been modernized using C++ and OOP techniques.

[TR] Bu repo, **C++** ve **Nesneye Yönelik Programlama (OOP)** yetkinliklerimi sergilemek amacıyla geliştirilmiş bir Solo Test çözücü içerir. Ayrıca proje kapsamında Makefile ve Docker teknolojileri de kullanılmıştır.

Bu proje aslında 2024 - 25 Akademik Yılı Yaz Döneminde **İstanbul teknik Üniversitesi (İTÜ) BLG 223E - Veri Yapıları** dersi kapsamında bir ödev olarak geliştirildi. Ancak daha sonra OOP ve C++ teknikleri kullanılarak modernize edildi.

---

## Technical Features

### 1. The Logic Behind The Solver

*   **[EN]** The solver uses a stack based **Depth-First Search (DFS)** algorithm to search through the game's state space and find the first state that meets the wanted remaining peg count.

*   **[TR]** Çözücü yığın tabanlı bir **DFS** algoritması kullanarak oyunun durum uzayında istenilen şartı sağlayacak ilk durumu bulacak şekilde oluşturuldu.

### 2. OOP Design & State Management

*   **[EN] Encapsulation:** All board logic and node relationships are encapsulated within a robust `Board` class.

*   **[TR] Kapsülleme:** Tüm tahta mantığı ve düğüm ilişkileri `Board` sınıfı içinde kapsüllenmiştir.

*   **[EN] Copying Game States:** Implemented a custom **Copy Constructor** to capture board states accurately during the search process.

*   **[TR] Oyun Durumlarını Kopyalama:** Arama süreci boyunca tahta durumlarını doğru şekilde yakalamak için özel bir **Copy Constructor** kullanıldı.

*   **[EN] Memory Management:** Features a dedicated **Destructor** to handle dynamic memory allocation, preventing any memory leaks.

*   **[TR] Bellek Yönetimi:** Dinamik bellek yönetimi ve bellek sızıntıları için özel bir **Destructor** içerir.

P.S. *The STL `std::stack` is used for efficient state management within the solve function. / solve fonksiyonu içerisinde verimli bellek yönetimi için `std::stack` kullanıldı.*

### 3. Future Optimization

**[EN] Memory Optimization & Performance:**

The current version uses a state copying approach for every possible move can be derived from the original state. While this ensures a correct solution for the given problem, I am aware that this is not the best way for the memory efficiency where methods like 'move and undo' exists. These optimizationsare noted for future work.

**[TR] Bellek Optimizasyonu ve Performans**

Mevcut versiyon her oyun ihtimalinin kopyalanması yklaşımı kullanıyor. Bu problemin çözümü için söz konusu yöntem işlevsel olmasına rağmen bellek yönetimi hamle yapıp geri alma gibi metotlarla arttırılabilir. Bu optimizasyonlar projenin ölçeklenebilirliği için not edilmiştir.

---

## Development & Deployment

### Environment / Ortam

The project is configured for cross-platform compatibility using **Docker** and **GNU Make**. / Proje, **Docker** ve **GNU Make** kullanılarak platformlar arası uyumluluk için yapılandırılmıştır.

### Prerequisites

* Docker (Recommended) OR
* GCC/G++ (c++17 Support) & Make

### Installation & Execution / Kurulum ve Çalıştırma

1. **Clone the repo**
    ```bash
    git clone https://github.com/angintaha/solotest-solver.git
    cd solotest-solver
    ```

2. **Using a Docker Container (Recommended)**
    ```bash
    docker build -t solotest-solver .
    docker run -it solotest-solver
    ```

3. **Using Local Make**
    ```bash
    make run
    ```

---

## Contact

**Ahmet Taha Angın**

* Istanbul Technical University
    * Computer Engineering
    * Mathematics Engineering (Double Major Program)

* **Email:** [taha.angin@gmail.com](mailto:taha.angin@gmail.com)

* **LinkedIn** [Ahmet Taha Angın](https://www.linkedin.com/in/angintaha/)
