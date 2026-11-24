int a,b,c;

void func_a(){
	a = 7;
}
int d, e;
int f[10];

int foo(int a){
	a = a + 3;
	return a;
}


int bar(int a, int b){	
	c = 4*a + 2*b;
	return c;
}

int main(){
 
	int i,j,k,l;
	
	i = 5;
	j = 6;
	
	func_a();
	println(a);
	
	k = foo(i);
	println(k);
	
	l = bar(i,j);
	println(l);
	
	j = 6 * bar(i,j) + 2 - 3 * foo(i);
	println(j);
	j = 6;

	k = foo(bar(i,j));
	println(k);	

	for(i = 0; i < 5; i++){
		f[i] = i;
		println(i);
	}
	println(i);
	for (j=0;j<10;j = j + 1){
		d = f[j];
		println(d);
	}
	
	return 0;
}
