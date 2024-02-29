# Homework 2 - Binary Search Tree

> Due: November 5, 2023 11:59 PM

**Topics**: Trees, Binary Search Trees, Set, Map, Red-black Tree

## Table of Contents

- [Homework 2 - Binary Search Tree](#homework-2---binary-search-tree)
  - [Table of Contents](#table-of-contents)
  - [Homework Spec](#homework-spec)
    - [Grading](#grading)
    - [TreeSet](#treeset)
    - [TreeMap](#treemap)
    - [BalancedTreeSet](#balancedtreeset)
    - [Memory Safety](#memory-safety)
    - [Submission](#submission)
  - [Setup](#setup)
    - [Option 1: VS Code with Local Dev Container](#option-1-vs-code-with-local-dev-container)
    - [Option 2: VS Code with Remote Dev](#option-2-vs-code-with-remote-dev)
    - [Option 3: Terminal](#option-3-terminal)
  - [Run/Debug](#rundebug)
    - [Run tests using VS Code](#run-tests-using-vs-code)
    - [Run tests using Terminal](#run-tests-using-terminal)

> ⚠️ DO NOT change files marked with
>
> ```cpp
> // DO NOT CHANGE THIS FILE
> ```

## Homework Spec

In this homework, you will write data structure **Binary Search Tree (BST)**
and balance the BST using **Red-Black Tree**'s self-balancing insertion.
And then build two template libraries based on BST: `TreeSet` and `TreeMap`.

You will implement `TreeSet` first and then implement `TreeMap` using `TreeSet`.

> In reality, `TreeSet` and `TreeMap` (ordered set and ordered map) are implemented using self-balanced trees (Red-Black Trees) to ensure a stable $O(\log n)$ search time.

### Grading

You will be graded only on the same (hidden) test cases your TAs created.

We provided some tests cases in [./tests](./tests). Feel free to modify and add more test cases, but the [./tests](./tests) in your submission will not be
graded. However, you will be able to see the results for your submitted test cases on Gradescope.

- `TreeSet` implementation - 60%
- `TreeMap` implementation - 15%
- `BalancedTreeSet` implementation - 15%
- Memory Safety - 10%

> **NOTE:** If you are running out of time to implement all methods (or just want to see the project can be compiled), please at least provide a syntactically valid empty method definition for each method in `lib/*.cpp`.

### TreeSet

- Check the definition for `BinaryTreeNode` in [lib/BinaryTreeNode.hpp](./lib/BinaryTreeNode.hpp).
- Check the spec in [lib/TreeSet.hpp](./lib/TreeSet.hpp) and implement all methods in [lib/TreeSet.cpp](./lib/TreeSet.cpp).
  - **NOTE**: you only need to implement `add` function of set, `remove` function is not required.
- Create test cases in [tests/TreeSetTest.cpp](./tests/TreeSetTest.cpp).

Since `TreeSet` is a generic class for type variable `T`,
we have to make sure that we can compare two elements of type `T` in order to build a BST.
Therefore, each `TreeSet` will need an `_comparator` to compare two elements of type `T`.
In this assignment, we will define the `_comparator` as a function with type

$$
cmp : T \times T \rightarrow \{-1, 0, 1\}
$$

where

- $cmp(x, y) = -1$ if $x < y$,
- $cmp(x, y) = 0$ if $x = y$,
- $cmp(x, y) = 1$ if $x > y$,

in C++, this function is declared as

```cpp
std::function<int(T, T)> _comparator;
```

See [lib/TreeSet.cpp](./lib/TreeSet.cpp) line 8 for provided example.

### TreeMap

- Check the spec in [lib/TreeMap.hpp](./lib/TreeMap.hpp) and implement all methods in [lib/TreeMap.cpp](./lib/TreeMap.cpp).
- Create test cases in [tests/TreeMapTest.cpp](./tests/TreeMapTest.cpp).

Keep in mind, since `TreeSet` is generic,
we can leverage it to implement a `TreeMap`.
This is done by storing entries as `std::pair<TKey, TValue>` in each tree node, 
where  `TKey`is the type of the key and`TValue` is the type of its associated value.

### BalancedTreeSet

- Use Red-Black Tree to keep the BST balanced, check definition `Color` in [lib/BinaryTreeNode.hpp](./lib/BinaryTreeNode.hpp).
- You only need to keep the tree balanced when **insertion (Textbook 13.3)**.
- Check the spec in [lib/TreeSet.hpp](./lib/TreeSet.hpp) and implement the following methods in [lib/TreeSet.cpp](./lib/TreeSet.cpp).
  - `void fix_violation(BinaryTreeNode<T> *z);`
  - `void rotate_left(BinaryTreeNode<T> *x);`
  - `void rotate_right(BinaryTreeNode<T> *y);`

**NOTE**
All the tests in `TreeSetTest` can be passed without balancing the tree.
If you don't intend to implement Red-Black Tree, please put these empty function at the end of [lib/TreeSet.cpp](./lib/TreeSet.cpp).

```cpp
// Red-Black Tree Functions
template <typename T>
void TreeSet<T>::rotate_left(BinaryTreeNode<T> *x) {}

template <typename T>
void TreeSet<T>::rotate_right(BinaryTreeNode<T> *y) {}

template <typename T>
void TreeSet<T>::fix_violation(BinaryTreeNode<T> *z) {}
```

If you leave this tree functions blank, you will still get at least 85% of the total score
(if your unbalanced BST implementation is correct).

### Memory Safety

We will run `valgrind --leak-check=full ./build/run_tests` against the hidden
test cases to check whether there is memory safety issues.

If your test cases are not comprehensive, `valgrind` may not be able to report
potential memory safety issues when you run it against your test cases.

If you do not fully implement the data structures, your score for memory safety
will be automatically discounted even if `valgrind` does not report error(s).

(For example, if you implement nothing, there will of course be no memory safety
issues, but you will receive a 0 on memory safety score).

### Submission

Use `./generate_submission.sh` and submit `hw2-submission.zip` on Gradescope.

## Setup

Use one of the following options to set up your environment.

> ⚠️ If you're a student, **DO NOT FORK** this repository because you cannot
> change the visibility of a forked repo to private. If you plan to use Git for
> version control (which is encouraged), run `rm -rf .git && git init` (or change remote) after
> setting up using one of the options below and push to your **private**
> repository. Any public repository containing part of this homework solution
> will be reported to SJA.

### Option 1: VS Code with Local Dev Container

- If Docker is not running, start Docker.

- Click the following button to set up the environment.

  [![Setup Local Dev Container](https://img.shields.io/static/v1?label=Local%20Dev%20Container&message=Setup&color=blue&logo=visualstudiocode)](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/ecs36c-fq2023/hw2)

- When asked for selecting a Kit to configure CMake, choose **GCC**.

### Option 2: VS Code with Remote Dev

- Connect VS Code to the remote host.

- Install **C/C++ Extension Pack** on Remote Server (if not already).

- Run the following command inside the integrated terminal.

  `git clone https://github.com/ecs36c-fq2023/hw2 ecs36c-hw2`

- Run `code ./ecs36c-hw2` to open the folder.

- When prompted to configure CMake, confirm and choose **GCC** when prompted for
  kit selection.

### Option 3: Terminal

- Run the following commands

  ```bash
  git clone https://github.com/ecs36c-fq2023/hw2 ecs36c-hw2
  cd ./ecs36c-hw2
  mkdir build
  cd build
  cmake ..
  ```

## Run/Debug

### Run tests using VS Code

Directly Launch via `Run -> start debugging` or `F5` function key.

### Run tests using Terminal

```bash
cd build
make
./run_tests
```
