
public class AscendingPriceCriteria implements Criteria {

    @Override
    public boolean compareCriteria(Produto criteria1, Produto criteria2){
        
        return !(criteria1.getPreco() >= criteria2.getPreco()); 
    }
}