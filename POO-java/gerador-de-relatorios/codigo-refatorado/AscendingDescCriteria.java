public class AscendingDescCriteria implements Criteria {

    @Override
    public boolean compareCriteria(Produto criteria1, Produto criteria2){
        return !(criteria1.getDescricao().compareToIgnoreCase(criteria2.getDescricao()) >= 0);
    }
}