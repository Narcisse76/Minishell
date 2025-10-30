# 🐚 Minishell - Mini-interpréteur de commandes Unix

<img width="198" height="168" alt="image" src="https://github.com/user-attachments/assets/cf9b5c4a-b8e8-4665-b1f9-b02bb2fe0829" />

Le projet Minishell consiste à créer un mini-shell en C, capable d’exécuter des commandes simples ou en pipeline, avec gestion des redirections, des builtins, et des variables d’environnement.
Ce projet permet de comprendre le fonctionnement interne d’un interpréteur de commandes et d’appliquer les notions de programmation système.

---

## ✅ Fonctionnalités principales

Exécution de commandes simples `ls`, `echo`,` `etc`.

Gestion des redirections `>`, `<`, `>>`, '<<'

Support des pipes pour enchaîner plusieurs commandes

Implémentation des builtins : `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`

Gestion des variables d’environnement

Gestion des erreurs et des signaux `Ctrl+C`, `Ctrl+D`

---

## 🔧 Compilation Make

`make`        → compile l’exécutable minishell  
`make clean`  → supprime les fichiers objets `.o`
`make fclean` → supprime les fichiers objets et l’exécutable  
`make re`     → recompile entièrement le projet

---

## 🧠 Ce qu’on y apprend

Compréhension des processus et appels système (fork, execve, wait)

Gestion des pipes et redirections en C

Manipulation des variables d’environnement

Développement d’un parseur et interpréteur de commandes

Rigueur et norme 42 appliquée à un projet complexe

---

## 🏁 Objectif

Créer un mini-shell fonctionnel, capable de traiter les commandes de manière autonome et robuste.
L’objectif est de maîtriser la programmation système, la gestion des processus et des signaux, et de préparer le terrain pour des projets avancés liés aux shells ou à l’automatisation sous Unix.
