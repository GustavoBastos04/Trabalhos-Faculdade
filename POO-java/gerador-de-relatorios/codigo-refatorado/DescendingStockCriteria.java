public class DescendingStockCriteria implements Criteria {

    @Override
    public boolean compareCriteria(Produto criteria1, Produto criteria2){
        return (criteria1.getQtdEstoque() > criteria2.getQtdEstoque());
    }
}