# 🚀 KFS-1 - Kernel From Scratch

**KFS-1** est la première étape du projet "Kernel From Scratch" de l'école 42. L'objectif est de créer un noyau x86 minimal, bootable via **GRUB**, capable d'initialiser une pile (stack) et d'interagir directement avec le matériel **VGA** pour afficher du contenu à l'écran.

---

## 🛠️ Fonctionnalités

* **Bootloader compatible Multiboot** : Le noyau respecte la norme **Multiboot 1** pour être chargé par GRUB sans encombre.
* **Initialisation de la Stack** : Mise en place d'une pile de **16 Ko** en assembleur, indispensable pour permettre l'exécution du code C.
* **VGA Masterpiece** : Affichage d'un portrait haute résolution (34x50 pixels perçus).
    * Utilisation de la technique du **demi-bloc** (`0xDF` / `▀`).
    * Implémentation du **tramage de Floyd-Steinberg** (Dithering) pour simuler des nuances complexes avec la palette limitée de 16 couleurs VGA.
* **Environnement Dockerisé** : Compilation isolée via Docker pour garantir la reproductibilité parfaite du binaire final.

---

## 📋 Prérequis

Avant de commencer, assure-toi d'avoir installé les outils suivants sur ton hôte :

* **Docker** & **Docker Compose** (pour l'environnement de build).
* **QEMU** (pour l'émulation matérielle) : `qemu-system-i386`.

---

## 🚀 Installation et Lancement

### 1. Préparer l'environnement
Lance le conteneur de build et compile les sources initiales :
```bash
make
```
Cette commande démarre le service builder et exécute le Makefile interne au dossier src.

### 2. Générer l'ISO
Pour créer l'image disque bootable (.iso) à l'intérieur du conteneur :
```Bash

docker compose exec builder make -C src iso
```
### 3. Lancer le Kernel
Utilise QEMU pour booter ton noyau et admirer le portrait :
Bash

qemu-system-i386 -cdrom src/kfs.iso

## 📂 Structure du Projet

* **`src/`** : Contient le code source du noyau (**ASM**, **C**, **Linker script**).
* **`Makefile` (racine)** : Gère l'orchestration des commandes via Docker Compose.
* **`docker-compose.yml`** : Définit le service de build (`builder`).
* **`subject.pdf`** : Les spécifications officielles du projet.

## 🎨 Détails Techniques : Le Rendu Portrait

Le rendu exploite le mode texte VGA standard ($80 \times 25$ caractères).

Pour maximiser la qualité du portrait de **Benjamin Netanyahu**, nous utilisons deux astuces majeures :

* **Caractère ASCII `0xDF` (▀)** : Ce caractère permet de colorer le haut (Foreground) et le bas (Background) d'une cellule séparément, doublant ainsi la résolution verticale perçue (passant de 25 à 50 pixels).
* **Dithering (Tramage)** : Un algorithme de diffusion d'erreur est appliqué lors de la conversion de la photo originale (2024x2947 px) vers les 16 couleurs matérielles du VGA, créant l'illusion de dégradés inexistants.

## 🧹 Nettoyage

* **Supprimer les fichiers objets** : `make clean`
* **Supprimer les binaires et le conteneur** : `make fclean`