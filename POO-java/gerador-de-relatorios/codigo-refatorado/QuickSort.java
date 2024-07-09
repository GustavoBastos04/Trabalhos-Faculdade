import java.util.Collections;
import java.util.List;
public class QuickSort implements Sort{

    public int particiona(List<Produto> products, Criteria criteria, int ini, int fim){

		int i = (ini - 1);
		int j = (fim + 1);

		while(true){

            do { 
                j--;
            } while (criteria.compareCriteria(products.get(j), products.get(ini)) == true);

            do {
                i++;
            } while(criteria.compareCriteria(products.get(ini), products.get(i)) == true);

				if(i < j){
					Collections.swap(products, i,j);
				}
			else return j;
		}
	}

    @Override
    public void ordena(List<Produto> products, Criteria criteria, int ini, int fim){
        
        if(ini < fim) {

				int q = particiona(products, criteria, ini, fim);
				
				ordena(products, criteria,ini, q);
				ordena(products,criteria, q + 1, fim);
			}
    }
}