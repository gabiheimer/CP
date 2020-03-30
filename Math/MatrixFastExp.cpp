struct Matrix {
	vector<vector<ll>> mat;

	Matrix(vector<ll> &line1){
        // line1 --> representa a operacao que eh tipo fibonacci
		this->mat.resize(baseSz);
		this->mat[0] = line1;
		for(int i = 1; i < baseSz; i++){
			for(int j = 0; j < baseSz; j++){
				if(j == i-1){
					this->mat[i].push_back(1);
				} else {
					this->mat[i].push_back(0);
				}
			}
		}
	}
	
	Matrix operator * (const Matrix p){
		Matrix *ans = new Matrix(line1M);
		
		for(int i = 0; i < baseSz; i++){
			for(int j = 0; j < baseSz; j++){
				for(int k = ans->mat[i][j] = 0; k < baseSz; k++){
					ans->mat[i][j] = (ans->mat[i][j] + mat[i][k] * p.mat[k][j]) % mod;
				}

			}
		}
		
		return *ans;
	}
};

// funcao para exponenciar a matriz
Matrix fExp(Matrix a, ll b){
	Matrix *ans = new Matrix(line1M);
	
	for(int i = 0; i < baseSz; i++){
		for(int j = 0; j < baseSz; j++){
			ans->mat[i][j] = (i == j);
		}
	}
	
	while(b) {
		if(b & 1) {
			(*ans) = (*ans) * a;
		}
		a = a*a;
		b >>= 1;
	}
	
	return *ans;
}
rix a, ll b){
	Matrix *ans = new Matrix(line1M);
	
	for(int i = 0; i < baseSz; i++){
		for(int j = 0; j < baseSz; j++){
			ans->mat[i][j] = (i == j);
		}
	}
	
	while(b) {
		if(b & 1
// funcao para multiplicar a matriz resultante com a base
// obs: pra dar certo a base tem que ficar ordenada do ultimo elemento pro primeiro
ll multComBase(Matrix m){
	ll resp = 0;
	for(int j = 0; j < baseSz; j++){
		resp += (m.mat[0][j] * base[j]) % mod;
	}
	
	return resp % mod;
}