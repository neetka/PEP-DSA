# SettleUp

A simple and efficient C++ project to simplify debt transactions between people by minimizing unnecessary money transfers.

This project calculates the **net balance** of every person and generates an optimized list of transactions so that:

* Everyone's final balance becomes zero
* Total money flow remains correct
* Number of transactions is minimized

---

# Problem Statement

During trips, events, or shared expenses, people often pay money on behalf of each other.

Over time, this creates complicated chains of debts like:

```text
Alice → Bob → Charlie → David
```

Many of these intermediate transactions are unnecessary because balances can cancel out.

The goal is to simplify the entire payment network into the minimum number of direct transactions.

---

# Example

## Input

```cpp
transactions = {
    {"Tom", "Jerry", "1000"},
    {"Jerry", "Spike", "1000"},
    {"Spike", "Tom", "500"}
};
```

---

# Step 1: Calculate Net Balance

| Person | Balance |
| ------ | ------- |
| Tom    | -500    |
| Jerry  | 0       |
| Spike  | +500    |

* Negative balance → needs to pay
* Positive balance → should receive
* Zero balance → already settled

---

# Step 2: Simplify Transactions

Instead of:

```text
Tom → Jerry → Spike
```

We directly settle:

```text
Tom → Spike : 500
```

---

# Optimized Output

```cpp
{
    {"Tom", "Spike", "500"}
}
```

---

# Approach

## 1. Compute Net Balance

For every transaction:

```text
A pays B amount X
```

We update:

```text
A balance -= X
B balance += X
```

After processing all transactions:

* Debtors have negative balance
* Creditors have positive balance

---

## 2. Separate Debtors and Creditors

We store:

* People who need to pay
* People who need to receive

in separate arrays.

---

## 3. Greedy Settlement

Using two pointers:

* One for debtors
* One for creditors

We settle balances greedily.

At every step:

```text
settle = min(debt, credit)
```

Then:

* Create transaction
* Update balances
* Move settled pointer

This continues until all balances become zero.

---

# Algorithm Flow

```text
Read Transactions
       ↓
Compute Net Balance
       ↓
Separate Debtors & Creditors
       ↓
Match Them Greedily
       ↓
Generate Optimized Transactions
       ↓
All Balances Become Zero
```

---

# Time Complexity

## Balance Calculation

```text
O(N)
```

Where `N` = number of transactions

---

## Settlement Process

```text
O(P)
```

Where `P` = number of people

---

## Overall Complexity

```text
O(N + P)
```

Efficient for large inputs.

---

# Data Structures Used

| Data Structure                   | Purpose                      |
| -------------------------------- | ---------------------------- |
| `unordered_map`                  | Store net balances           |
| `vector<pair<string,long long>>` | Store debtors and creditors  |
| `vector<vector<string>>`         | Store final optimized result |

---


# Why This Works

This method works because:

* Total incoming and outgoing money remains unchanged
* Intermediate transactions are removed
* Every step settles at least one person's balance completely
* Final balances become zero for everyone

---

# Concepts Used

* Greedy Algorithm
* Hash Maps
* Net Flow Balancing
* Transaction Optimization
* Two Pointer Technique

---

# Real-World Applications

* Expense splitting apps
* Group trip settlement systems
* Payment optimization platforms
* Financial reconciliation systems

---

# Conclusion

This project efficiently minimizes unnecessary debt transactions by converting a complex payment network into a simplified optimized settlement system.

Instead of following long payment chains, users can directly settle balances with the minimum required transfers.
