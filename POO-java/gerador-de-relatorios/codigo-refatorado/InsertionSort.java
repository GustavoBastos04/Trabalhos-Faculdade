import java.util.List;
public class InsertionSort implements Sort {
	
    @Override
    public void ordena(List<Produto> products, Criteria criteria, int ini, int fim){

        for(int i = ini; i <= fim; i++){

				Produto x = products.get(i);				
				int j = (i - 1);

				while(j >= ini){

                    if(criteria.compareCriteria( products.get(j), x) == true){
                        products.set(j+1, products.get(j));
                        j--;
                    }
                    else break;
                    products.set(j + 1, x);
                }
				
			}
    }
}