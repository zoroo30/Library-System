void registeration(void)
{
    //when register auto-initialize numOfBooksBorrowed to zero
    fgets(member_array[mm].name,sizeof(member_array[mm].name),stdin);
    getchar();
    scanf(" %d",&(member_array[mm].ID));
    scanf(" %d",&(member_array[mm].address.buildNum));
    fgets(member_array[mm].address.city,sizeof(member_array[mm].address.city),stdin);
    fgets(member_array[mm].address.street,sizeof(member_array[mm].address.street),stdin);
    scanf(" %d%d",&(member_array[mm].mobile),&(member_array[mm].age));
    fgets(member_array[mm].email.name,sizeof(member_array[mm].email.name),stdin);
    fgets(member_array[mm].email.domain,sizeof(member_array[mm].email.domain),stdin);
    member_array[mm].booksBorrowed=0;
    mm++;
    return ;

}
