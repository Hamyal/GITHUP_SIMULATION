# GITHUP_SIMULATION
Welcome to giithup simulation project in data structure
// Define a helper function for DFS traversal of repositories
// Helper function for DFS traversal to find repository
Repository* DFSFindRepository(treeimplmentation* root, const string& repoName) {
    if (root->get_node().find(repoName) != root->get_node().end()) {
        return root->get_node()[repoName]->get_Repository();
    } else {
        for (auto& child : root->get_node()) {
            Repository* repo = DFSFindRepository(child.second, repoName);
            if (repo) return repo;
        }
    }
    return nullptr;
}

// Add file function with DFS
void githupsimulation::addfileDFS(treeimplmentation* root, const string& repoName, const string& fileName) {
    Repository* repo = DFSFindRepository(root, repoName);
    if (repo) {
        File newFile(fileName);
        repo->addFile(newFile);
        cout << "The file is added to the repository" << endl;
        writerepo();
    } else {
        cout << "The repository is not found" << endl;
    }
}

// Add file function with DFS wrapper
void githupsimulation::addfile(const string& username, const string& repoName, const string& fileName) {
    if (Users_REPOSIT.find(username) == Users_REPOSIT.end()) {
        cout << "The user does not exist" << endl;
        return;
    }
    treeimplmentation* root = Users_REPOSIT[username];
    addfileDFS(root, repoName, fileName);
}

// Delete file function with DFS
void githupsimulation::deletefileDFS(treeimplmentation* root, const string& repoName, const string& fileName) {
    Repository* repo = DFSFindRepository(root, repoName);
    if (repo) {
        repo->deleteFile(fileName);
        cout << "The file is deleted from the repository" << endl;
        writerepo();
    } else {
        cout << "The repository is not found" << endl;
    }
}

// Delete file function with DFS wrapper
void githupsimulation::deletefile(const string& username, const string& repoName, const string& fileName) {
    if (Users_REPOSIT.find(username) == Users_REPOSIT.end()) {
        cout << "The user does not exist" << endl;
        return;
    }
    treeimplmentation* root = Users_REPOSIT[username];
    deletefileDFS(root, repoName, fileName);
}

void DFSRepository(treeimplmentation* root, unordered_set<string>& visited) {
    visited.insert(root->get_user());
    for (auto& child : root->get_node()) {
        if (visited.find(child.first) == visited.end()) {
            Repository* repo = child.second->get_Repository();
            // Perform any operation needed on the repository
            // For example, print repository details
            cout << "Repository Name: " << repo->getName() << endl;
            // Perform DFS on the child repository
            DFSRepository(child.second, visited);
        }
    }
}

// Login function with DFS
void githupsimulation::login(string& loggedInUser) {
    string username, password;
    cout << "Enter the username: ";
    cin >> username;

    if (users.find(username) == users.end()) {
        cout << "the username is not found" << endl;
        return;
    }

    cout << "Enter the password: ";
    cin >> password;

    if (users[username].get_Password() == password) {
        cout << "Login successful" << endl;
        loggedInUser = username;
    } else {
        cout << "Incorrect password" << endl;
    }
}

// Create repository function with DFS
void githupsimulation::createRepositoryDFS(treeimplmentation* root, const string& repoName, bool isPublic, int commitCount) {
    if (root->get_node().find(repoName) == root->get_node().end()) {
        Repository* repo = new Repository(repoName, isPublic);
        for (int i = 0; i < commitCount; i++) {
            commitment commit("commit");
            repo->addCommit(commit);
        }
        root->addChild(repoName, repo);
    } else {
        cout << "The repository already exists" << endl;
        return;
    }
}

// Create repository function with DFS wrapper
void githupsimulation::createRepository(const string& username, const string& repoName, bool isPublic, int commitCount) {
    if (Users_REPOSIT.find(username) == Users_REPOSIT.end()) {
        treeimplmentation* root = new treeimplmentation(nullptr);
        Users_REPOSIT[username] = root;
    }

    treeimplmentation* root = Users_REPOSIT[username];
    createRepositoryDFS(root, repoName, isPublic, commitCount);
}

// Delete repository function with DFS
void githupsimulation::deleteRepositoryDFS(treeimplmentation* root, const string& repoName) {
    if (root->get_node().find(repoName) != root->get_node().end()) {
        delete root->get_node()[repoName];
        root->get_node().erase(repoName);
        cout << "The repository is deleted successfully" << endl;
    } else {
        cout << "The repository is not found" << endl;
        return;
    }
}

// Delete repository function with DFS wrapper
void githupsimulation::deleteRepository(const string& username, const string& repoName) {
    if (Users_REPOSIT.find(username) == Users_REPOSIT.end()) {
        cout << "The user does not exist" << endl;
        return;
    }

    treeimplmentation* root = Users_REPOSIT[username];
    deleteRepositoryDFS(root, repoName);
}

// Fork function with DFS
void githupsimulation::Fork(const string& sourceUsername, const string& sourceRepoName, const string& targetUsername) {
    if (Users_REPOSIT.find(sourceUsername) == Users_REPOSIT.end()) {
        cout << "The source user is not found" << endl;
        return;
    }

    treeimplmentation* sourceRoot = Users_REPOSIT[sourceUsername];
    if (sourceRoot->get_node().find(sourceRepoName) == sourceRoot->get_node().end()) {
        cout << "The source repository is not found" << endl;
        return;
    }

    // Perform Fork operation using DFS if needed
    // Example: DFSRepository(sourceRoot, visited);
    // Perform the rest of the fork operation
    cout << "Fork operation completed" << endl;
}

void githupsimulation::StatsrepositoryDFS(const string& username, const string& repoName, unordered_map<string, bool>& visited) {
    if (visited.find(username) == visited.end()) {
        cout << "the user is not found" << endl;
        return;
    }

    visited[username] = true;
    treeimplmentation* root = Users_REPOSIT[username];

    if (root->get_node().find(repoName) == root->get_node().end()) {
        cout << "the repository is not found" << endl;
        return;
    }

    Repository* repo = root->get_node()[repoName]->get_Repository();

    int forkCount = countfork(username, repoName);
    cout << "the repository name : " << repo->getName() << endl;
    cout << "the file number : " << repo->getFileCount() << endl;
    cout << "the commitment message : " << repo->Commit_Count() << endl;
    cout << "the total no of fork: " << forkCount << endl;
    cout << "the commit messages are:" << endl;
    const vector<string>& commitMessages = repo->Messages_commits();
    for (size_t i = 0; i < commitMessages.size(); i++) {
        cout << i + 1 << ". " << commitMessages[i] << endl;
    }
}

void githupsimulation::DFS(const string& user, unordered_map<string, bool>& visited) {
    visited[user] = true;
    for (const auto& follower : followGraph[user]) {
        if (!visited[follower]) {
            DFS(follower, visited);
        }
    }
}

void githupsimulation::Statsrepository(const string& username, const string& repoName) {
    unordered_map<string, bool> visited;
    for (const auto& user : Users_REPOSIT) {
        visited[user.first] = false;
    }

    if (visited.find(username) == visited.end()) {
        cout << "the user is not found" << endl;
        return;
    }

    StatsrepositoryDFS(username, repoName, visited);
}

void githupsimulation::Folllow(const string& follower, const string& following) {
    if (users.find(follower) == users.end() || users.find(following) == users.end()) {
        cout << "no user found!" << endl;
        return;
    }

    followGraph[follower].insert(following);
    users[follower].Followers_add();
    cout << follower << " is now following " << following << endl;
}

void githupsimulation::Unfolllow(const string& follower, const string& following) {
    bool Find_Follow = users.find(follower) != users.end();
    bool followingFound = users.find(following) != users.end();
    if (!Find_Follow || !followingFound) {
        cout << "no user exists " << endl;
        return;
    }

    bool isFollowing = false;
    auto add_f = followGraph.find(follower);
    if (add_f != followGraph.end()) {
        auto followingIt = add_f->second.find(following);
        if (followingIt != add_f->second.end()) {
            add_f->second.erase(followingIt);
            isFollowing = true;
        }
    }

    if (isFollowing) {
        users[follower].Followers_delete();
        cout << follower << " is unfollowing " << following << endl;
    } else {
        cout << follower << " was not following " << following << endl;
    }
}
