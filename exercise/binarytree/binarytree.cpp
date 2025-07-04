
#include "binarytree.hpp"

namespace lasd {

  /* ************************************************************************ */

    // Confronta due alberi binari per determinare se sono uguali.
    template <typename Data>
    inline bool BinaryTree<Data>::operator==(const BinaryTree& anotherBinaryTree) const noexcept {
    // Controlla se le dimensioni degli alberi sono diverse, se sì, restituisce false.
    if(this->size != anotherBinaryTree.size)
        return false;
    // Crea iteratori pre-ordine per entrambi gli alberi.
    BTPreOrderIterator iteratorThis(*this);
    BTPreOrderIterator iteratorOther(anotherBinaryTree);
    // Itera attraverso entrambi gli alberi finché non si verificano le seguenti condizioni:
    // 1. Un iteratore raggiunge la fine dell'albero (Terminated)
    // 2. Gli elementi visitati dagli iteratori sono diversi.
    while (!(iteratorThis.Terminated() || iteratorOther.Terminated())) {
        if (*iteratorThis != *iteratorOther) // Se gli elementi visitati dagli iteratori sono diversi, restituisce false.
            return false;
        ++iteratorThis; // Avanza l'iteratore per l'albero this.
        ++iteratorOther; // Avanza l'iteratore per l'altro albero.
        }
    
        return true; // Se il ciclo termina senza restituire false, significa che gli alberi sono uguali.
    }

  /* ************************************************************************ */

    // Attraversa l'albero binario utilizzando la funzione di attraversamento specificata.
    template <typename Data>
    void BinaryTree<Data>::Traverse(const TraverseFun function) const {
    // Controlla se l'albero non è vuoto.
    if(!this->Empty()) {
        PreOrderTraverse(function); // Se l'albero non è vuoto, esegue l'attraversamento pre-ordine utilizzando la funzione specificata.

        }
    }

  /* ************************************************************************ */

    // Esegue un attraversamento pre-ordine dell'albero binario utilizzando la funzione di attraversamento specificata.
    template <typename Data>
    void BinaryTree<Data>::PreOrderTraverse(const TraverseFun function) const {
    // Verifica se l'albero non è vuoto.
    if(!(this->Empty())) {
        // Se l'albero non è vuoto, chiama la funzione di ausilio per l'attraversamento pre-ordine passando il puntatore alla radice dell'albero
        // e la funzione di attraversamento specificata.
        AuxPreOrderTraversable(&this->Root(), function);
        }
    }

  /* ************************************************************************ */

   // Esegue un attraversamento post-ordine dell'albero binario utilizzando la funzione di attraversamento specificata.
    template <typename Data>
    void BinaryTree<Data>::PostOrderTraverse(const TraverseFun function) const {
    // Verifica se l'albero non è vuoto.
    if(!this->Empty()) {
        // Se l'albero non è vuoto, chiama la funzione di ausilio per l'attraversamento post-ordine passando il puntatore alla radice dell'albero 
        // e la funzione di attraversamento specificata.
        AuxPostOrderTraversable(&this->Root(), function);
        }
    }

  /* ************************************************************************ */

    // Esegue un attraversamento in-ordine dell'albero binario utilizzando la funzione di attraversamento specificata.
    template <typename Data>
    void BinaryTree<Data>::InOrderTraverse(const TraverseFun function) const {
    // Verifica se l'albero non è vuoto.
    if(!this->Empty()) {
        // Se l'albero non è vuoto, chiama la funzione di ausilio per l'attraversamento in-ordine passando il puntatore alla radice dell'albero 
        //e la funzione di attraversamento specificata.
        AuxInOrderTraversable(&this->Root(), function);
        }
    }

  /* ************************************************************************ */

     // Esegue un attraversamento in ampiezza dell'albero binario utilizzando la funzione di attraversamento specificata.
    template <typename Data>
    void BinaryTree<Data>::BreadthTraverse(const TraverseFun function) const {
    // Verifica se l'albero non è vuoto.
    if(!this->Empty()) {
        // Se l'albero non è vuoto, chiama la funzione di ausilio per l'attraversamento in ampiezza passando il puntatore alla radice dell'albero 
        //e la funzione di attraversamento specificata.
        AuxBreadthTraversable(&this->Root(), function);
        }
    }

  /* ************************************************************************ */

    // Funzione ausiliaria per l'attraversamento pre-ordine dell'albero binario.
    template <typename Data>
    void BinaryTree<Data>::AuxPreOrderTraversable(const Node* node, const TraverseFun function) const {
    // Esegue la funzione di attraversamento sull'elemento del nodo corrente.
    function(node->Element());
    // Se il nodo ha un figlio sinistro, esegue ricorsivamente l'attraversamento pre-ordine sul figlio sinistro.
    if(node->HasLeftChild())
        AuxPreOrderTraversable(&node->LeftChild(), function);
    // Se il nodo ha un figlio destro, esegue ricorsivamente l'attraversamento pre-ordine sul figlio destro.
    if(node->HasRightChild())
        AuxPreOrderTraversable(&node->RightChild(), function);
    }

  /* ************************************************************************ */

   // Funzione ausiliaria per l'attraversamento post-ordine dell'albero binario.
    template <typename Data>
    void BinaryTree<Data>::AuxPostOrderTraversable(const Node* node, const TraverseFun function) const {
    // Se il nodo ha un figlio sinistro, esegue ricorsivamente l'attraversamento post-ordine sul figlio sinistro.
    if(node->HasLeftChild())
        AuxPostOrderTraversable(&node->LeftChild(), function);
    // Se il nodo ha un figlio destro, esegue ricorsivamente l'attraversamento post-ordine sul figlio destro.
    if(node->HasRightChild())
        AuxPostOrderTraversable(&node->RightChild(), function);
    // Esegue la funzione di attraversamento sull'elemento del nodo corrente dopo aver attraversato i suoi figli.
    function(node->Element());
    }

  /* ************************************************************************ */

    // Funzione ausiliaria per l'attraversamento in-ordine dell'albero binario.
    template <typename Data>
    void BinaryTree<Data>::AuxInOrderTraversable(const Node* node, const TraverseFun function) const {
    // Se il nodo ha un figlio sinistro, esegue ricorsivamente l'attraversamento in-ordine sul figlio sinistro.
    if(node->HasLeftChild()) 
        AuxInOrderTraversable(&node->LeftChild(), function);
    // Esegue la funzione di attraversamento sull'elemento del nodo corrente dopo aver attraversato il figlio sinistro.
    function(node->Element());
    // Se il nodo ha un figlio destro, esegue ricorsivamente l'attraversamento in-ordine sul figlio destro.
    if(node->HasRightChild())
        AuxInOrderTraversable(&node->RightChild(), function);
    }

  /* ************************************************************************ */

   // Funzione ausiliaria per l'attraversamento in ampiezza dell'albero binario.
    template <typename Data>
    void BinaryTree<Data>::AuxBreadthTraversable(const Node* node, const TraverseFun function) const {
    // Crea una coda per gestire i nodi durante l'attraversamento in ampiezza.
    lasd::QueueLst<const BinaryTree<Data>::Node *> queue;
    // Se il nodo iniziale non è nullo, lo aggiunge alla coda.
    if(node != nullptr)
        queue.Enqueue(node);
    // Finché la coda non è vuota, continua a processare i nodi.
    while (!queue.Empty()) {
        // Ottiene e rimuove il nodo corrente dalla testa della coda.
        const BinaryTree<Data>::Node *currentNode = queue.HeadNDequeue();
        // Esegue la funzione di attraversamento sull'elemento del nodo corrente.
        function(currentNode->Element());
        // Se il nodo corrente ha un figlio sinistro, lo aggiunge alla coda.
        if(currentNode->HasLeftChild())
            queue.Enqueue(&currentNode->LeftChild());
        // Se il nodo corrente ha un figlio destro, lo aggiunge alla coda.
        if(currentNode->HasRightChild())
            queue.Enqueue(&currentNode->RightChild());
        }
    }

  /* ************************************************************************ */
    // MutableBinaryTree

    template <typename Data>
    void MutableBinaryTree<Data>::PreOrderMap(MapFun function){
    // Controlla se l'albero non è vuoto prima di iniziare il mapping
    if(!(this->Empty()))
        AuxPreOrderMap(&this->Root(), function); // Chiama la funzione di supporto per il mapping in ordine di pre-ordine

    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::PostOrderMap(MapFun function){
    // Controlla se l'albero non è vuoto prima di iniziare il mapping
    if(!(this->Empty()))
        AuxPostOrderMap(&this->Root(), function); // Chiama la funzione di supporto per il mapping in ordine di post-ordine

    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::InOrderMap(MapFun function){
    // Controlla se l'albero non è vuoto prima di iniziare il mapping
    if(!(this->Empty()))
        AuxInOrderMap(&this->Root(), function); // Chiama la funzione di supporto per il mapping in ordine di in-ordine

    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::BreadthMap(MapFun function){
    // Controlla se l'albero non è vuoto prima di iniziare il mapping
    if(!(this->Empty()))
        AuxBreadthMap(&this->Root(), function); // Chiama la funzione di supporto per il mapping in ampiezza

    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::AuxPreOrderMap(MutableNode* node, MapFun function) {
    // Applica la funzione di mapping al nodo corrente
    function(node->Element());
    // Se il nodo ha un figlio sinistro, chiama ricorsivamente AuxPreOrderMap su di esso
    if(node->HasLeftChild())
        AuxPreOrderMap(&node->LeftChild(), function);
    // Se il nodo ha un figlio destro, chiama ricorsivamente AuxPreOrderMap su di esso
    if(node->HasRightChild())
        AuxPreOrderMap(&node->RightChild(), function);

    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::AuxPostOrderMap(MutableNode* node, MapFun function){
    // Se il nodo ha un figlio sinistro, chiama ricorsivamente AuxPostOrderMap su di esso
    if(node->HasLeftChild())
        AuxPostOrderMap(&node->LeftChild(), function);
    // Se il nodo ha un figlio destro, chiama ricorsivamente AuxPostOrderMap su di esso
    if(node->HasRightChild())
        AuxPostOrderMap(&node->RightChild(), function);

    function(node->Element()); // Applica la funzione di mapping al nodo corrente dopo aver visitato i suoi figli
    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::AuxInOrderMap(MutableNode* node, MapFun function){
    // Se il nodo ha un figlio sinistro, chiama ricorsivamente AuxInOrderMap su di esso
    if(node->HasLeftChild())
        AuxInOrderMap(&node->LeftChild(), function);
    // Applica la funzione di mapping al nodo corrente durante l'attraversamento in ordine di in-ordine
    function(node->Element());
    // Se il nodo ha un figlio destro, chiama ricorsivamente AuxInOrderMap su di esso
    if(node->HasRightChild())
        AuxInOrderMap(&node->RightChild(), function);
    }

  /* ************************************************************************ */

    template <typename Data>
    void MutableBinaryTree<Data>::AuxBreadthMap(MutableNode* node, MapFun function){
    // Crea una coda per l'attraversamento in ampiezza
    lasd::QueueLst<MutableBinaryTree<Data>::MutableNode *> queue;
    // Se il nodo non è nullo, lo inserisce nella coda
    if(node!=nullptr)
        queue.Enqueue(node);
    while (!queue.Empty()) {
        // Estrae il nodo corrente dalla testa della coda
        MutableBinaryTree<Data>::MutableNode *currentNode = queue.HeadNDequeue();
        function(currentNode->Element()); // Applica la funzione di mapping al nodo corrente
        // Se il nodo corrente ha un figlio sinistro, lo inserisce nella coda
        if(currentNode->HasLeftChild())
            queue.Enqueue(&currentNode->LeftChild());
        // Se il nodo corrente ha un figlio destro, lo inserisce nella coda
        if(currentNode->HasRightChild())
            queue.Enqueue(&currentNode->RightChild());
        }
    }

  /* ************************************************************************ */
    //BTPreOrderIterator

   template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& anotherBinaryTree) {
    // Se l'albero anotherIterator non è vuoto, imposta il nodo radice corrente sull'elemento radice di anotherIterator
    if (!anotherBinaryTree.Empty()) 
        root = current = &anotherBinaryTree.Root();
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &anotherIterator) : stack(anotherIterator.stack) {
    // Copia il puntatore alla radice e il puntatore al nodo corrente dall'iteratore anotherIterator
    root = anotherIterator.root;
    current = anotherIterator.current;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& anotherIterator) noexcept : stack(std::move(anotherIterator.stack)) {
    // Sposta i dati dello stack da anotherIterator a questo iteratore
    // Scambia i puntatori alla radice e al nodo corrente tra this e anotherIterator
    std::swap(root, anotherIterator.root);
    std::swap(current, anotherIterator.current); 
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente, il puntatore alla radice e lo stack dall'iteratore anotherIterator a questo iteratore
    current = anotherIterator.current;
    root = anotherIterator.root;
    stack = anotherIterator.stack;
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& anotherIterator) noexcept {
    // Sposta i dati dello stack da anotherIterator a questo iteratore
    // Scambia i puntatori alla radice e al nodo corrente tra this e other
    std::swap(current, anotherIterator.current);
    std::swap(root, anotherIterator.root);
    std::swap(stack, anotherIterator.stack);
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator &anotherIterator) const noexcept {
    // Restituisce true se il nodo corrente e lo stack di questo iteratore sono uguali a quelli di anotherIterator
    return (current == anotherIterator.current && stack == anotherIterator.stack);
    }

  /* ************************************************************************ */

    template <typename Data>
    const Data& BTPreOrderIterator<Data>::operator*() const {
    // Se l'iteratore è terminato, lancia un'eccezione std::out_of_range
    if (Terminated())
        throw std::out_of_range("BTPreOrderIterator termina con operator*()");
    else
        // Restituisce il riferimento costante all'elemento del nodo corrente
        return current->Element();
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if (!Terminated()) {
        // Se il nodo corrente ha un figlio sinistro
        if (current->HasLeftChild()) {
            // Se il nodo corrente ha anche un figlio destro, inserisce il figlio destro nello stack
            if (current->HasRightChild())
                stack.Push(&current->RightChild());
            // Sposta il puntatore al nodo corrente al figlio sinistro
            current = &(current->LeftChild());
        } else if (current->HasRightChild()) { // Se il nodo corrente ha solo un figlio destro
            // Sposta il puntatore al nodo corrente al figlio destro
            current = &(current->RightChild());
        } else if (!stack.Empty()) { // Se il nodo corrente non ha figli e lo stack non è vuoto
            // Estrae il prossimo nodo dalla cima dello stack e lo imposta come il nodo corrente
            current = stack.TopNPop();
        } else { // Se il nodo corrente non ha figli e lo stack è vuoto, l'iteratore è terminato
            current = nullptr;
        }
    } else { // Se l'iteratore è terminato, lancia un'eccezione std::out_of_range
        throw std::out_of_range("BTPreOrderIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator++");
    }
    return *this;
    }

  /* ************************************************************************ */
    // BTPreOrderMutableIterator

   template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente, il puntatore alla radice e lo stack dall'iteratore other a questo iteratore
    this->current = anotherIterator.current;
    this->root = anotherIterator.root;
    this->stack = anotherIterator.stack;
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& anotherIterator) noexcept {
    // Sposta i dati dello stack da other a questo iteratore
    // Scambia i puntatori alla radice e al nodo corrente tra this e anotherIterator
    std::swap(this->current, anotherIterator.current);
    std::swap(this->root, anotherIterator.root);
    std::swap(this->stack, anotherIterator.stack);
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    Data& BTPreOrderMutableIterator<Data>::operator*() {
    // Se il puntatore al nodo corrente non è nullo, restituisce il riferimento all'elemento del nodo corrente
    if (this->current != nullptr) 
        return const_cast<Data&>((this->current)->Element());
    else
        // Altrimenti, lancia un'eccezione std::out_of_range
        throw std::out_of_range("BTBreadthMutableIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator*()."); 
    }

  /* ************************************************************************ */
    // BTPostOrderIterator
    
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& anotherIterator){
    // Se l'albero other è vuoto, imposta il puntatore alla radice su nullptr
    if (anotherIterator.Empty())
        root = nullptr;
    else
        // Altrimenti, imposta il puntatore alla radice sull'elemento radice di anotherIterator
        root = &anotherIterator.Root();
    // Trova il nodo più a sinistra nel sottoalbero radicato a root e lo imposta come il nodo corrente
    current = DeepestLeftLeaf(root);
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& anotherIterator) {
    // Copia lo stack, il puntatore alla radice e il puntatore al nodo corrente dall'iteratore anotherIterator
    stack = anotherIterator.stack;
    root = anotherIterator.root;
    current = anotherIterator.current;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& anotherIterator) noexcept : stack(std::move(anotherIterator.stack)) {
    // Sposta i dati dello stack da other a questo iteratore
    // Scambia i puntatori alla radice e al nodo corrente tra this e anotherIterator
    std::swap(current, anotherIterator.current);
    std::swap(root, anotherIterator.root); 
    }

  /* ************************************************************************ */

    template <typename Data>
    const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::DeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual){
    // Controlla se il nodo attuale non è nullo
    if(actual!=nullptr){ 
        while(actual->HasLeftChild()){ // Continua finché il nodo attuale ha un figlio sinistro
            stack.Push(actual); // Push del nodo attuale nello stack
            actual = &(actual->LeftChild()); // Aggiorna il puntatore attuale al figlio sinistro del nodo attuale
        }
        if(actual->HasRightChild()){ // Se il nodo attuale ha un figlio destro
            stack.Push(actual); // Push del nodo attuale nello stack
            actual = &(actual->RightChild()); // Aggiorna il puntatore attuale al figlio destro del nodo attuale
            actual = DeepestLeftLeaf(actual); // Chiamata ricorsiva per trovare il nodo più a sinistra nel sottoalbero destro
        }
    }
    return actual; // Restituisce il puntatore al nodo più a sinistra
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente dal "anotherIterator" all'oggetto corrente
    current = anotherIterator.current;
    // Assegna il puntatore alla radice dell'albero dal "anotherIterator" all'oggetto corrente
    root = anotherIterator.root;
    // Assegna lo stato dello stack dal "anotherIterator" all'oggetto corrente
    stack = anotherIterator.stack;
    // Restituisce l'oggetto corrente per consentire l'assegnazione concatenata
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& anotherIterator) noexcept {
    // Swap dei puntatori al nodo corrente tra gli iteratori corrente e "anotherIterator"
    std::swap(current, anotherIterator.current);
    // Swap dei puntatori alla radice dell'albero tra gli iteratori corrente e "anotherIterator"
    std::swap(root, anotherIterator.root);
    // Swap dello stato dello stack tra gli iteratori corrente e "anotherIterator"
    std::swap(stack, anotherIterator.stack);
    // Restituisce l'oggetto corrente per consentire l'assegnazione concatenata
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator &anotherIterator) const noexcept {
    // Verifica se il puntatore al nodo corrente è uguale tra l'iteratore corrente e "anotherIterator",
    // e se lo stato dello stack è uguale tra gli iteratori corrente e "anotherIterator"
    return (current == anotherIterator.current && stack == anotherIterator.stack);
    }

  /* ************************************************************************ */

    template <typename Data>
    const Data& BTPostOrderIterator<Data>::operator*() const {
    // Verifica se l'iteratore è terminato
    if (Terminated())
        throw std::out_of_range("BTPostOrderIterator termina con operator*()");
    else
        // Restituisce il riferimento costante all'elemento del nodo corrente
        return current->Element();
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() {
    // Controlla se l'iteratore non è terminato
    if (!(Terminated())) {
        if (!(stack.Empty())) {
            // Se il nodo in cima allo stack ha un figlio destro e il figlio destro non è uguale al nodo corrente
            if (stack.Top()->HasRightChild() && !(&(stack.Top()->RightChild()) == current)) {
                // Aggiorna il puntatore corrente al figlio destro del nodo in cima allo stack
                current = &(stack.Top()->RightChild());
                // Trova il nodo più a sinistra nel sottoalbero destro
                current = DeepestLeftLeaf(current);
            } else {
                // Altrimenti, aggiorna il puntatore corrente al nodo in cima allo stack e rimuove il nodo dallo stack
                current = stack.TopNPop();
            }
        } else {
            // Se lo stack è vuoto, imposta il puntatore corrente a nullptr
            current = nullptr;
        }
    } else {
        // Se l'iteratore è terminato, lancia un'eccezione
        throw std::out_of_range("BTPostOrderIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator++");
    }
    return *this; // Restituisce l'iteratore corrente per consentire l'incremento concatenato
    }

  /* ************************************************************************ */
    // BTPostOrderMutableIterator

    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente dal "anotherIterator" all'oggetto corrente
    this->current = anotherIterator.current;
    // Assegna il puntatore alla radice dell'albero dal "anotherIterator" all'oggetto corrente
    this->root = anotherIterator.root;
    // Assegna lo stato dello stack dal "anotherIterator" all'oggetto corrente
    this->stack = anotherIterator.stack;
    
    return *this; // Restituisce l'oggetto corrente per consentire l'assegnazione concatenata
    }

  /* ************************************************************************ */

    template <typename Data>
    BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& anotherIterator) noexcept {
    // Scambia i puntatori al nodo corrente tra l'iteratore corrente e "anotherIterator"
    std::swap(this->current, anotherIterator.current);
    // Scambia i puntatori alla radice dell'albero tra l'iteratore corrente e "anotherIterator"
    std::swap(this->root, anotherIterator.root);
    // Scambia lo stato dello stack tra l'iteratore corrente e "anotherIterator"
    std::swap(this->stack, anotherIterator.stack);
    
    return *this; // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    }

  /* ************************************************************************ */

    template <typename Data>
    Data& BTPostOrderMutableIterator<Data>::operator*() {
    // Verifica se il puntatore al nodo corrente non è nullo
    if (this->current != nullptr)
        // Restituisce un riferimento non costante all'elemento del nodo corrente,
        // utilizzando const_cast per rimuovere la costante
        return const_cast<Data&>((this->current)->Element());
    else
        // Se il puntatore al nodo corrente è nullo, lancia un'eccezione
        throw std::out_of_range("BTPostOrderMutableIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator*()");
    }

  /* ************************************************************************ */
    // BTInOrderIterator

    template <typename Data>
    const typename BinaryTree<Data>::Node *BTInOrderIterator<Data>::FindDeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual) {
    // Continua finché il nodo attuale non è nullo e ha un figlio sinistro
    while (actual != nullptr && (actual->HasLeftChild())) {
        // Push del nodo attuale nello stack
        stack.Push(actual);
        // Aggiorna il puntatore attuale al figlio sinistro del nodo attuale
        actual = &actual->LeftChild();
    }
    
    return actual; // Restituisce il puntatore al nodo più a sinistra
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &anotherIterator) {
    // Verifica se l'albero passato come parametro è vuoto
    if (anotherIterator.Empty())
        root = nullptr; // Se è vuoto, imposta il puntatore alla radice a nullptr
    else
        root = &anotherIterator.Root(); // Altrimenti, imposta il puntatore alla radice all'indirizzo della radice dell'albero passato
    
    current = FindDeepestLeftLeaf(root); // Trova il nodo più a sinistra nell'albero e imposta il puntatore corrente
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& anotherIterator) {
    // Copia lo stato dello stack dall'iteratore "anotherIterator"
    stack = anotherIterator.stack;
    // Copia il puntatore alla radice dall'iteratore "anotherIterator"
    root = anotherIterator.root;
    // Copia il puntatore corrente dall'iteratore "anotherIterator"
    current = anotherIterator.current;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& anotherIterator) noexcept : stack(std::move(anotherIterator.stack)) {
    // Sposta lo stack da "anotherIterator" all'iteratore corrente utilizzando std::move
    // Questo trasferimento permette di evitare la duplicazione dei dati nello stack
    std::swap(current, anotherIterator.current);
    // Scambia il puntatore alla radice tra l'iteratore corrente e "anotherIterator"
    std::swap(root, anotherIterator.root); 
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& anotherIterator) {
    // Assegna il puntatore corrente dall'iteratore "anotherIterator" all'iteratore corrente
    current = anotherIterator.current;
    // Assegna il puntatore alla radice dall'iteratore "anotherIterator" all'iteratore corrente
    root = anotherIterator.root;
    // Assegna lo stato dello stack dall'iteratore "anotherIterator" all'iteratore corrente
    stack = anotherIterator.stack;
    // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& anotherIterator) noexcept {
    // Scambia i puntatori al nodo corrente tra l'iteratore corrente e "anotherIterator"
    std::swap(current, anotherIterator.current);
    // Scambia i puntatori alla radice dell'albero tra l'iteratore corrente e "anotherIterator"
    std::swap(root, anotherIterator.root);
    // Scambia lo stato dello stack tra l'iteratore corrente e "anotherIterator"
    std::swap(stack, anotherIterator.stack);
    // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    return *this;
    }

  /* ************************************************************************ */

    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &anotherIterator) const noexcept {
    // Verifica se il puntatore al nodo corrente e lo stato dello stack sono uguali tra l'iteratore corrente e "anotherIterator"
    return (current == anotherIterator.current && stack == anotherIterator.stack);
    }

  /* ************************************************************************ */

    template <typename Data>
    const Data& BTInOrderIterator<Data>::operator*() const {
    // Verifica se l'iteratore è terminato
    if (Terminated())
        throw std::out_of_range("BTInOrderIterator termina con operator*()");
    else
        
        return current->Element(); // Restituisce il riferimento costante all'elemento del nodo corrente
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator++() {
    // Verifica se l'iteratore non è terminato
    if(!(Terminated())) {
        // Se lo stack è vuoto e il nodo corrente non ha un figlio destro, imposta il puntatore corrente a nullptr
        if((stack.Empty()) && !(current->HasRightChild()))
            current = nullptr;
        else { 
            // Se il nodo corrente ha un figlio destro, trova il nodo più a sinistra nel sottoalbero destro
            if(current->HasRightChild()){
                current = FindDeepestLeftLeaf(&current->RightChild());
            }
            // Altrimenti, imposta il puntatore corrente al nodo in cima allo stack e rimuove il nodo dallo stack
            else
                current = stack.TopNPop();
        }
    }
    else
        // Se l'iteratore è terminato, lancia un'eccezione
        throw std::out_of_range("BTInOrderIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator++");

    return *this; // Restituisce l'iteratore corrente per consentire l'incremento concatenato
    }

  /* ************************************************************************ */
    // BTInOrderMutableIterator

    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente dall'iteratore "anotherIterator" all'iteratore corrente
    this->current = anotherIterator.current;
    // Assegna il puntatore alla radice dall'iteratore "anotherIterator" all'iteratore corrente
    this->root = anotherIterator.root;
    // Assegna lo stato dello stack dall'iteratore "anotherIterator" all'iteratore corrente
    this->stack = anotherIterator.stack;
    
    return *this; // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    }

  /* ************************************************************************ */

    template <typename Data>
    BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator&& anotherIterator) noexcept {
    // Scambia i puntatori al nodo corrente tra l'iteratore corrente e "anotherIterator"
    std::swap(this->current, anotherIterator.current);
    // Scambia i puntatori alla radice dell'albero tra l'iteratore corrente e "anotherIterator"
    std::swap(this->root, anotherIterator.root);
    // Scambia lo stato dello stack tra l'iteratore corrente e "anotherIterator"
    std::swap(this->stack, anotherIterator.stack);
    
    return *this; // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
}

  /* ************************************************************************ */

    template <typename Data>
    Data& BTInOrderMutableIterator<Data>::operator*() {
    // Verifica se il puntatore al nodo corrente non è nullo
    if (this->current != nullptr)
        // Restituisce un riferimento non costante all'elemento del nodo corrente,
        // utilizzando const_cast per rimuovere la costante
        return const_cast<Data&>((this->current)->Element());
    else
        // Se il puntatore al nodo corrente è nullo, lancia un'eccezione
        throw std::out_of_range("BTInOrderMutableIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator*()");
}

  /* ************************************************************************ */
    //BTBreadthIterator

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& anotherIterator) {
    // Verifica se l'albero passato come parametro è vuoto
    if (anotherIterator.Empty()) {
        // Se è vuoto, imposta i puntatori alla radice e al nodo corrente a nullptr
        root = current = nullptr;
    } else {
        // Altrimenti, imposta i puntatori alla radice e al nodo corrente all'indirizzo della radice dell'albero passato
        root = current = &anotherIterator.Root();
    }
    }

  /* ************************************************************************ */

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator &anotherIterator) {
    // Copia la coda di nodi da "anotherIterator" all'iteratore corrente
    queue = anotherIterator.queue;
    // Copia i puntatori alla radice e al nodo corrente da "anotherIterator" all'iteratore corrente
    root = current = anotherIterator.current;
    }

  /* ************************************************************************ */

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& anotherIterator) noexcept : queue(std::move(anotherIterator.queue)) {
    // Sposta la coda di nodi da "anotherIterator" all'iteratore corrente utilizzando std::move
    // Questo trasferimento permette di evitare la duplicazione dei dati nella coda
    std::swap(root, anotherIterator.root);
    // Scambia i puntatori alla radice e al nodo corrente tra l'iteratore corrente e "anotherIterator"
    std::swap(current, anotherIterator.current); 
    }

  /* ************************************************************************ */

    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente dall'iteratore "anotherIterator" all'iteratore corrente
    current = anotherIterator.current;
    // Assegna il puntatore alla radice dall'iteratore "anotherIterator" all'iteratore corrente
    root = anotherIterator.root;
    // Assegna la coda di nodi dall'iteratore "anotherIterator" all'iteratore corrente
    queue = anotherIterator.queue;

    return *this; // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    }

  /* ************************************************************************ */

    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& anotherIterator) noexcept {
    // Scambia i puntatori al nodo corrente tra l'iteratore corrente e "anotherIterator"
    std::swap(current, anotherIterator.current);
    // Scambia i puntatori alla radice dell'albero tra l'iteratore corrente e "anotherIterator"
    std::swap(root, anotherIterator.root);
    // Scambia la coda di nodi tra l'iteratore corrente e "anotherIterator"
    std::swap(queue, anotherIterator.queue);
    // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    return *this;
}

  /* ************************************************************************ */

    template <typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &anotherIterator) const noexcept {
    // Verifica se il puntatore al nodo corrente e la coda di nodi sono uguali tra l'iteratore corrente e "anotherIterator"
    return (current == anotherIterator.current && queue == anotherIterator.queue);
    }

  /* ************************************************************************ */

    template <typename Data>
    const Data& BTBreadthIterator<Data>::operator*() const {
    // Verifica se l'iteratore è terminato
    if (Terminated())
        // Se l'iteratore è terminato, lancia un'eccezione
        throw std::out_of_range("BTBreadthIterator termina con operator*()");
    else
        return current->Element(); // Restituisce il riferimento costante all'elemento del nodo corrente
    }

  /* ************************************************************************ */

    template <typename Data>
    BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    // Verifica se l'iteratore non è terminato
    if (!(Terminated())) {
        // Se il nodo corrente ha un figlio sinistro, inserisci il puntatore a tale figlio nella coda
        if (current->HasLeftChild())
            queue.Enqueue(&(current->LeftChild())); 
        // Se il nodo corrente ha un figlio destro, inserisci il puntatore a tale figlio nella coda
        if (current->HasRightChild())
            queue.Enqueue(&(current->RightChild()));
        // Se la coda non è vuota, assegna il nodo in testa alla coda come nodo corrente e rimuovilo dalla coda
        if (!queue.Empty())
            current = queue.HeadNDequeue();
        // Se la coda è vuota, imposta il nodo corrente a nullptr
        else
            current = nullptr;
    }
    else
        // Se l'iteratore è terminato, lancia un'eccezione
        throw std::out_of_range("BTBreadthIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator++");

    return *this;// Restituisce l'iteratore corrente per consentire l'incremento concatenato
}

  /* ************************************************************************ */
    //BTBreadthMutableIterator 

    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& anotherIterator) {
    // Assegna il puntatore al nodo corrente dall'iteratore "anotherIterator" all'iteratore corrente
    this->current = anotherIterator.current;
    // Assegna il puntatore alla radice dall'iteratore "anotherIterator" all'iteratore corrente
    this->root = anotherIterator.root;
    // Assegna la coda di nodi dall'iteratore "anotherIterator" all'iteratore corrente
    this->queue = anotherIterator.queue;

    return *this; // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    }

  /* ************************************************************************ */

    template <typename Data>
    BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& anotherIterator) noexcept {
    // Scambia i puntatori al nodo corrente tra l'iteratore corrente e "anotherIterator"
    std::swap(this->current, anotherIterator.current);
    // Scambia i puntatori alla radice dell'albero tra l'iteratore corrente e "anotherIterator"
    std::swap(this->root, anotherIterator.root);
    // Scambia la coda di nodi tra l'iteratore corrente e "anotherIterator"
    std::swap(this->queue, anotherIterator.queue);
    
    return *this; // Restituisce l'iteratore corrente per consentire l'assegnazione concatenata
    }

  /* ************************************************************************ */

    template <typename Data>
    Data& BTBreadthMutableIterator<Data>::operator*() {
    // Verifica se il puntatore al nodo corrente non è nullo
    if (this->current != nullptr)
        // Restituisce un riferimento non costante all'elemento del nodo corrente,
        // utilizzando const_cast per rimuovere la costante
        return const_cast<Data&>((this->current)->Element());
    else
        // Se il puntatore al nodo corrente è nullo, lancia un'eccezione
        throw std::out_of_range("BTBreadthMutableIterator è al di fuori dell'intervallo consentito durante l'uso dell'operator*()");
    }

  /* ************************************************************************ */

}