#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;
vector<vector<string>> minimizeCashFlow(vector<vector<string>>& transactions) {
    unordered_map<string, long long> balance;
    // Step 1: Compute balances
    for (auto &t : transactions) {

        string from = t[0];
        string to = t[1];
        long long amount = stoll(t[2]);

        balance[from] -= amount;
        balance[to] += amount;
    }

    // Step 2: Separate debtors and creditors
    vector<pair<string, long long>> debtors;
    vector<pair<string, long long>> creditors;
    for (auto &entry : balance) {
        string person = entry.first;
        long long amt = entry.second;
        if (amt < 0) {
            debtors.push_back({person, -amt});
        }
        else if (amt > 0) {
            creditors.push_back({person, amt});
        }
    }

    // Step 3: Greedy settlement
    vector<vector<string>> result;
    int i = 0;
    int j = 0;
    while (i < debtors.size() && j < creditors.size()) {
        string debtor = debtors[i].first;
        string creditor = creditors[j].first;
        long long debt = debtors[i].second;
        long long credit = creditors[j].second;
        long long settle = min(debt, credit);
        result.push_back({
            debtor,
            creditor,
            to_string(settle)
        });
        debtors[i].second -= settle;
        creditors[j].second -= settle;
        if (debtors[i].second == 0)
            i++;
        if (creditors[j].second == 0)
            j++;
    }
    return result;
}

int main() {
    int n;
    cout << "Enter number of transactions: ";
    cin >> n;
    vector<vector<string>> transactions;
    cout << "Enter transactions in format: From To Amount\n";
    for (int i = 0; i < n; i++) {
        string from, to;
        long long amount;
        cin >> from >> to >> amount;
        transactions.push_back({
            from,
            to,
            to_string(amount)
        });
    }
    vector<vector<string>> result = minimizeCashFlow(transactions);
    cout << "\nOptimized Transactions:\n";
    if (result.empty()) {
        cout << "All balances are already settled.\n";
        return 0;
    }
    for (auto &t : result) {
        cout << t[0] << " pays " 
             << t[1] << " : " 
             << t[2] << endl;
    }
    return 0;
}