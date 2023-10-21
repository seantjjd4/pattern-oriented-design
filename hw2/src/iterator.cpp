// #include "iterator.h"
// #include "folder.h"

// Folder::FolderIterator::FolderIterator(Folder* composite)
//     :_host(composite) {
//         _version = _host->_getVersion();
//     }

// void Folder::FolderIterator::first() {
//     if (_host->_getVersion() != _version) {
//         throw ("Iterator unavailable! -> --Folder structure changed--");
//     }
//     _current = _host->_nodes.begin();
// }

// Node * Folder::FolderIterator::currentItem() const {
//     return *_current;
// }

// void Folder::FolderIterator::next() {
//     if (_host->_getVersion() != _version) {
//         throw ("Iterator unavailable! -> --Folder structure changed--");
//     }
//     _current++;
// }

// bool Folder::FolderIterator::isDone() const {
//     return _current == _host->_nodes.end();
// }
