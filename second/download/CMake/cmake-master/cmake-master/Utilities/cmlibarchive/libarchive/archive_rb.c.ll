; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_rb.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_rb_tree = type { %struct.archive_rb_node*, %struct.archive_rb_tree_ops* }
%struct.archive_rb_node = type { [2 x %struct.archive_rb_node*], i64 }
%struct.archive_rb_tree_ops = type { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, i32 (%struct.archive_rb_node*, i8*)* }

; Function Attrs: nounwind uwtable
define void @__archive_rb_tree_init(%struct.archive_rb_tree* %rbt, %struct.archive_rb_tree_ops* %ops) #0 !dbg !20 {
entry:
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %ops.addr = alloca %struct.archive_rb_tree_ops*, align 8
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !83, metadata !84), !dbg !85
  store %struct.archive_rb_tree_ops* %ops, %struct.archive_rb_tree_ops** %ops.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree_ops** %ops.addr, metadata !86, metadata !84), !dbg !87
  %0 = load %struct.archive_rb_tree_ops*, %struct.archive_rb_tree_ops** %ops.addr, align 8, !dbg !88
  %1 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !89
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %1, i32 0, i32 1, !dbg !90
  store %struct.archive_rb_tree_ops* %0, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !91
  %2 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !92
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %2, i32 0, i32 0, !dbg !93
  store %struct.archive_rb_node* null, %struct.archive_rb_node** %rbt_root, align 8, !dbg !94
  ret void, !dbg !95
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree* %rbt, i8* %key) #0 !dbg !49 {
entry:
  %retval = alloca %struct.archive_rb_node*, align 8
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %key.addr = alloca i8*, align 8
  %compare_key = alloca i32 (%struct.archive_rb_node*, i8*)*, align 8
  %parent = alloca %struct.archive_rb_node*, align 8
  %diff = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !96, metadata !84), !dbg !97
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !98, metadata !84), !dbg !99
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_rb_node*, i8*)** %compare_key, metadata !100, metadata !84), !dbg !101
  %0 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !102
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %0, i32 0, i32 1, !dbg !103
  %1 = load %struct.archive_rb_tree_ops*, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !103
  %rbto_compare_key = getelementptr inbounds %struct.archive_rb_tree_ops, %struct.archive_rb_tree_ops* %1, i32 0, i32 1, !dbg !104
  %2 = load i32 (%struct.archive_rb_node*, i8*)*, i32 (%struct.archive_rb_node*, i8*)** %rbto_compare_key, align 8, !dbg !104
  store i32 (%struct.archive_rb_node*, i8*)* %2, i32 (%struct.archive_rb_node*, i8*)** %compare_key, align 8, !dbg !101
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %parent, metadata !105, metadata !84), !dbg !106
  %3 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !107
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %3, i32 0, i32 0, !dbg !108
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !108
  store %struct.archive_rb_node* %4, %struct.archive_rb_node** %parent, align 8, !dbg !106
  br label %while.cond, !dbg !109

while.cond:                                       ; preds = %if.end, %entry
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !110
  %cmp = icmp eq %struct.archive_rb_node* %5, null, !dbg !110
  %lnot = xor i1 %cmp, true, !dbg !112
  br i1 %lnot, label %while.body, label %while.end, !dbg !113

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %diff, metadata !114, metadata !84), !dbg !117
  %6 = load i32 (%struct.archive_rb_node*, i8*)*, i32 (%struct.archive_rb_node*, i8*)** %compare_key, align 8, !dbg !118
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !119
  %8 = load i8*, i8** %key.addr, align 8, !dbg !120
  %call = call i32 %6(%struct.archive_rb_node* %7, i8* %8), !dbg !121
  store i32 %call, i32* %diff, align 4, !dbg !117
  %9 = load i32, i32* %diff, align 4, !dbg !122
  %cmp1 = icmp eq i32 %9, 0, !dbg !124
  br i1 %cmp1, label %if.then, label %if.end, !dbg !125

if.then:                                          ; preds = %while.body
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !126
  store %struct.archive_rb_node* %10, %struct.archive_rb_node** %retval, align 8, !dbg !127
  br label %return, !dbg !127

if.end:                                           ; preds = %while.body
  %11 = load i32, i32* %diff, align 4, !dbg !128
  %cmp2 = icmp sgt i32 %11, 0, !dbg !129
  %conv = zext i1 %cmp2 to i32, !dbg !129
  %idxprom = sext i32 %conv to i64, !dbg !130
  %12 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !130
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %12, i32 0, i32 0, !dbg !131
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !130
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !130
  store %struct.archive_rb_node* %13, %struct.archive_rb_node** %parent, align 8, !dbg !132
  br label %while.cond, !dbg !133

while.end:                                        ; preds = %while.cond
  store %struct.archive_rb_node* null, %struct.archive_rb_node** %retval, align 8, !dbg !135
  br label %return, !dbg !135

return:                                           ; preds = %while.end, %if.then
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %retval, align 8, !dbg !136
  ret %struct.archive_rb_node* %14, !dbg !136
}

; Function Attrs: nounwind uwtable
define %struct.archive_rb_node* @__archive_rb_tree_find_node_geq(%struct.archive_rb_tree* %rbt, i8* %key) #0 !dbg !52 {
entry:
  %retval = alloca %struct.archive_rb_node*, align 8
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %key.addr = alloca i8*, align 8
  %compare_key = alloca i32 (%struct.archive_rb_node*, i8*)*, align 8
  %parent = alloca %struct.archive_rb_node*, align 8
  %last = alloca %struct.archive_rb_node*, align 8
  %diff = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !137, metadata !84), !dbg !138
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !139, metadata !84), !dbg !140
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_rb_node*, i8*)** %compare_key, metadata !141, metadata !84), !dbg !142
  %0 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !143
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %0, i32 0, i32 1, !dbg !144
  %1 = load %struct.archive_rb_tree_ops*, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !144
  %rbto_compare_key = getelementptr inbounds %struct.archive_rb_tree_ops, %struct.archive_rb_tree_ops* %1, i32 0, i32 1, !dbg !145
  %2 = load i32 (%struct.archive_rb_node*, i8*)*, i32 (%struct.archive_rb_node*, i8*)** %rbto_compare_key, align 8, !dbg !145
  store i32 (%struct.archive_rb_node*, i8*)* %2, i32 (%struct.archive_rb_node*, i8*)** %compare_key, align 8, !dbg !142
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %parent, metadata !146, metadata !84), !dbg !147
  %3 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !148
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %3, i32 0, i32 0, !dbg !149
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !149
  store %struct.archive_rb_node* %4, %struct.archive_rb_node** %parent, align 8, !dbg !147
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %last, metadata !150, metadata !84), !dbg !151
  store %struct.archive_rb_node* null, %struct.archive_rb_node** %last, align 8, !dbg !151
  br label %while.cond, !dbg !152

while.cond:                                       ; preds = %if.end4, %entry
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !153
  %cmp = icmp eq %struct.archive_rb_node* %5, null, !dbg !153
  %lnot = xor i1 %cmp, true, !dbg !155
  br i1 %lnot, label %while.body, label %while.end, !dbg !156

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %diff, metadata !157, metadata !84), !dbg !159
  %6 = load i32 (%struct.archive_rb_node*, i8*)*, i32 (%struct.archive_rb_node*, i8*)** %compare_key, align 8, !dbg !160
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !161
  %8 = load i8*, i8** %key.addr, align 8, !dbg !162
  %call = call i32 %6(%struct.archive_rb_node* %7, i8* %8), !dbg !163
  store i32 %call, i32* %diff, align 4, !dbg !159
  %9 = load i32, i32* %diff, align 4, !dbg !164
  %cmp1 = icmp eq i32 %9, 0, !dbg !166
  br i1 %cmp1, label %if.then, label %if.end, !dbg !167

if.then:                                          ; preds = %while.body
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !168
  store %struct.archive_rb_node* %10, %struct.archive_rb_node** %retval, align 8, !dbg !169
  br label %return, !dbg !169

if.end:                                           ; preds = %while.body
  %11 = load i32, i32* %diff, align 4, !dbg !170
  %cmp2 = icmp slt i32 %11, 0, !dbg !172
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !173

if.then3:                                         ; preds = %if.end
  %12 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !174
  store %struct.archive_rb_node* %12, %struct.archive_rb_node** %last, align 8, !dbg !175
  br label %if.end4, !dbg !176

if.end4:                                          ; preds = %if.then3, %if.end
  %13 = load i32, i32* %diff, align 4, !dbg !177
  %cmp5 = icmp sgt i32 %13, 0, !dbg !178
  %conv = zext i1 %cmp5 to i32, !dbg !178
  %idxprom = sext i32 %conv to i64, !dbg !179
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !179
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %14, i32 0, i32 0, !dbg !180
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !179
  %15 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !179
  store %struct.archive_rb_node* %15, %struct.archive_rb_node** %parent, align 8, !dbg !181
  br label %while.cond, !dbg !182

while.end:                                        ; preds = %while.cond
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %last, align 8, !dbg !184
  store %struct.archive_rb_node* %16, %struct.archive_rb_node** %retval, align 8, !dbg !185
  br label %return, !dbg !185

return:                                           ; preds = %while.end, %if.then
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %retval, align 8, !dbg !186
  ret %struct.archive_rb_node* %17, !dbg !186
}

; Function Attrs: nounwind uwtable
define %struct.archive_rb_node* @__archive_rb_tree_find_node_leq(%struct.archive_rb_tree* %rbt, i8* %key) #0 !dbg !53 {
entry:
  %retval = alloca %struct.archive_rb_node*, align 8
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %key.addr = alloca i8*, align 8
  %compare_key = alloca i32 (%struct.archive_rb_node*, i8*)*, align 8
  %parent = alloca %struct.archive_rb_node*, align 8
  %last = alloca %struct.archive_rb_node*, align 8
  %diff = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !187, metadata !84), !dbg !188
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !189, metadata !84), !dbg !190
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_rb_node*, i8*)** %compare_key, metadata !191, metadata !84), !dbg !192
  %0 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !193
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %0, i32 0, i32 1, !dbg !194
  %1 = load %struct.archive_rb_tree_ops*, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !194
  %rbto_compare_key = getelementptr inbounds %struct.archive_rb_tree_ops, %struct.archive_rb_tree_ops* %1, i32 0, i32 1, !dbg !195
  %2 = load i32 (%struct.archive_rb_node*, i8*)*, i32 (%struct.archive_rb_node*, i8*)** %rbto_compare_key, align 8, !dbg !195
  store i32 (%struct.archive_rb_node*, i8*)* %2, i32 (%struct.archive_rb_node*, i8*)** %compare_key, align 8, !dbg !192
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %parent, metadata !196, metadata !84), !dbg !197
  %3 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !198
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %3, i32 0, i32 0, !dbg !199
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !199
  store %struct.archive_rb_node* %4, %struct.archive_rb_node** %parent, align 8, !dbg !197
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %last, metadata !200, metadata !84), !dbg !201
  store %struct.archive_rb_node* null, %struct.archive_rb_node** %last, align 8, !dbg !201
  br label %while.cond, !dbg !202

while.cond:                                       ; preds = %if.end4, %entry
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !203
  %cmp = icmp eq %struct.archive_rb_node* %5, null, !dbg !203
  %lnot = xor i1 %cmp, true, !dbg !205
  br i1 %lnot, label %while.body, label %while.end, !dbg !206

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %diff, metadata !207, metadata !84), !dbg !209
  %6 = load i32 (%struct.archive_rb_node*, i8*)*, i32 (%struct.archive_rb_node*, i8*)** %compare_key, align 8, !dbg !210
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !211
  %8 = load i8*, i8** %key.addr, align 8, !dbg !212
  %call = call i32 %6(%struct.archive_rb_node* %7, i8* %8), !dbg !213
  store i32 %call, i32* %diff, align 4, !dbg !209
  %9 = load i32, i32* %diff, align 4, !dbg !214
  %cmp1 = icmp eq i32 %9, 0, !dbg !216
  br i1 %cmp1, label %if.then, label %if.end, !dbg !217

if.then:                                          ; preds = %while.body
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !218
  store %struct.archive_rb_node* %10, %struct.archive_rb_node** %retval, align 8, !dbg !219
  br label %return, !dbg !219

if.end:                                           ; preds = %while.body
  %11 = load i32, i32* %diff, align 4, !dbg !220
  %cmp2 = icmp sgt i32 %11, 0, !dbg !222
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !223

if.then3:                                         ; preds = %if.end
  %12 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !224
  store %struct.archive_rb_node* %12, %struct.archive_rb_node** %last, align 8, !dbg !225
  br label %if.end4, !dbg !226

if.end4:                                          ; preds = %if.then3, %if.end
  %13 = load i32, i32* %diff, align 4, !dbg !227
  %cmp5 = icmp sgt i32 %13, 0, !dbg !228
  %conv = zext i1 %cmp5 to i32, !dbg !228
  %idxprom = sext i32 %conv to i64, !dbg !229
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !229
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %14, i32 0, i32 0, !dbg !230
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !229
  %15 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !229
  store %struct.archive_rb_node* %15, %struct.archive_rb_node** %parent, align 8, !dbg !231
  br label %while.cond, !dbg !232

while.end:                                        ; preds = %while.cond
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %last, align 8, !dbg !234
  store %struct.archive_rb_node* %16, %struct.archive_rb_node** %retval, align 8, !dbg !235
  br label %return, !dbg !235

return:                                           ; preds = %while.end, %if.then
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %retval, align 8, !dbg !236
  ret %struct.archive_rb_node* %17, !dbg !236
}

; Function Attrs: nounwind uwtable
define i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %self) #0 !dbg !54 {
entry:
  %retval = alloca i32, align 4
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %compare_nodes = alloca i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, align 8
  %parent = alloca %struct.archive_rb_node*, align 8
  %tmp = alloca %struct.archive_rb_node*, align 8
  %position = alloca i32, align 4
  %rebalance = alloca i32, align 4
  %diff = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !237, metadata !84), !dbg !238
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !239, metadata !84), !dbg !240
  call void @llvm.dbg.declare(metadata i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)** %compare_nodes, metadata !241, metadata !84), !dbg !242
  %0 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !243
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %0, i32 0, i32 1, !dbg !244
  %1 = load %struct.archive_rb_tree_ops*, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !244
  %rbto_compare_nodes = getelementptr inbounds %struct.archive_rb_tree_ops, %struct.archive_rb_tree_ops* %1, i32 0, i32 0, !dbg !245
  %2 = load i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)** %rbto_compare_nodes, align 8, !dbg !245
  store i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)* %2, i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)** %compare_nodes, align 8, !dbg !242
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %parent, metadata !246, metadata !84), !dbg !247
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %tmp, metadata !248, metadata !84), !dbg !249
  call void @llvm.dbg.declare(metadata i32* %position, metadata !250, metadata !84), !dbg !251
  call void @llvm.dbg.declare(metadata i32* %rebalance, metadata !252, metadata !84), !dbg !253
  %3 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !254
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %3, i32 0, i32 0, !dbg !255
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !255
  store %struct.archive_rb_node* %4, %struct.archive_rb_node** %tmp, align 8, !dbg !256
  %5 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !257
  %rbt_root3 = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %5, i32 0, i32 0, !dbg !258
  %6 = bitcast %struct.archive_rb_node** %rbt_root3 to i8*, !dbg !259
  %7 = bitcast i8* %6 to %struct.archive_rb_node*, !dbg !260
  store %struct.archive_rb_node* %7, %struct.archive_rb_node** %parent, align 8, !dbg !261
  store i32 0, i32* %position, align 4, !dbg !262
  br label %while.cond, !dbg !263

while.cond:                                       ; preds = %if.end, %entry
  %8 = load %struct.archive_rb_node*, %struct.archive_rb_node** %tmp, align 8, !dbg !264
  %cmp = icmp eq %struct.archive_rb_node* %8, null, !dbg !264
  %lnot = xor i1 %cmp, true, !dbg !266
  br i1 %lnot, label %while.body, label %while.end, !dbg !267

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %diff, metadata !268, metadata !84), !dbg !270
  %9 = load i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)** %compare_nodes, align 8, !dbg !271
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %tmp, align 8, !dbg !272
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !273
  %call = call i32 %9(%struct.archive_rb_node* %10, %struct.archive_rb_node* %11), !dbg !274
  store i32 %call, i32* %diff, align 4, !dbg !270
  %12 = load i32, i32* %diff, align 4, !dbg !275
  %cmp5 = icmp eq i32 %12, 0, !dbg !277
  br i1 %cmp5, label %if.then, label %if.end, !dbg !278

if.then:                                          ; preds = %while.body
  store i32 0, i32* %retval, align 4, !dbg !279
  br label %return, !dbg !279

if.end:                                           ; preds = %while.body
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %tmp, align 8, !dbg !281
  store %struct.archive_rb_node* %13, %struct.archive_rb_node** %parent, align 8, !dbg !282
  %14 = load i32, i32* %diff, align 4, !dbg !283
  %cmp6 = icmp sgt i32 %14, 0, !dbg !284
  %conv = zext i1 %cmp6 to i32, !dbg !284
  store i32 %conv, i32* %position, align 4, !dbg !285
  %15 = load i32, i32* %position, align 4, !dbg !286
  %idxprom = zext i32 %15 to i64, !dbg !287
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !287
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %16, i32 0, i32 0, !dbg !288
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !287
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !287
  store %struct.archive_rb_node* %17, %struct.archive_rb_node** %tmp, align 8, !dbg !289
  br label %while.cond, !dbg !290

while.end:                                        ; preds = %while.cond
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !292
  %19 = ptrtoint %struct.archive_rb_node* %18 to i64, !dbg !292
  %20 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !292
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %20, i32 0, i32 1, !dbg !292
  %21 = load i64, i64* %rb_info, align 8, !dbg !292
  %and = and i64 %21, 3, !dbg !292
  %or = or i64 %19, %and, !dbg !292
  %22 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !292
  %rb_info7 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %22, i32 0, i32 1, !dbg !292
  store i64 %or, i64* %rb_info7, align 8, !dbg !292
  %23 = load i32, i32* %position, align 4, !dbg !293
  %tobool = icmp ne i32 %23, 0, !dbg !293
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !293

cond.true:                                        ; preds = %while.end
  %24 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !294
  %rb_info8 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %24, i32 0, i32 1, !dbg !294
  %25 = load i64, i64* %rb_info8, align 8, !dbg !294
  %or9 = or i64 %25, 2, !dbg !294
  store i64 %or9, i64* %rb_info8, align 8, !dbg !294
  br label %cond.end, !dbg !294

cond.false:                                       ; preds = %while.end
  %26 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !295
  %rb_info10 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %26, i32 0, i32 1, !dbg !295
  %27 = load i64, i64* %rb_info10, align 8, !dbg !295
  %and11 = and i64 %27, -3, !dbg !295
  store i64 %and11, i64* %rb_info10, align 8, !dbg !295
  br label %cond.end, !dbg !295

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %or9, %cond.true ], [ %and11, %cond.false ], !dbg !296
  %28 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !298
  %29 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !300
  %rbt_root12 = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %29, i32 0, i32 0, !dbg !301
  %30 = bitcast %struct.archive_rb_node** %rbt_root12 to i8*, !dbg !302
  %31 = bitcast i8* %30 to %struct.archive_rb_node*, !dbg !303
  %cmp13 = icmp eq %struct.archive_rb_node* %28, %31, !dbg !304
  br i1 %cmp13, label %if.then15, label %if.else, !dbg !305

if.then15:                                        ; preds = %cond.end
  %32 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !306
  %rb_info16 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %32, i32 0, i32 1, !dbg !306
  %33 = load i64, i64* %rb_info16, align 8, !dbg !306
  %and17 = and i64 %33, -2, !dbg !306
  store i64 %and17, i64* %rb_info16, align 8, !dbg !306
  store i32 0, i32* %rebalance, align 4, !dbg !308
  br label %if.end26, !dbg !309

if.else:                                          ; preds = %cond.end
  %34 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !310
  %rb_info18 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %34, i32 0, i32 1, !dbg !310
  %35 = load i64, i64* %rb_info18, align 8, !dbg !310
  %or19 = or i64 %35, 1, !dbg !310
  store i64 %or19, i64* %rb_info18, align 8, !dbg !310
  %36 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !312
  %cmp20 = icmp eq %struct.archive_rb_node* %36, null, !dbg !312
  br i1 %cmp20, label %land.end, label %land.rhs, !dbg !312

land.rhs:                                         ; preds = %if.else
  %37 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !313
  %rb_info22 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %37, i32 0, i32 1, !dbg !313
  %38 = load i64, i64* %rb_info22, align 8, !dbg !313
  %and23 = and i64 %38, 1, !dbg !313
  %cmp24 = icmp ne i64 %and23, 0, !dbg !313
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.else
  %39 = phi i1 [ false, %if.else ], [ %cmp24, %land.rhs ]
  %land.ext = zext i1 %39 to i32, !dbg !315
  store i32 %land.ext, i32* %rebalance, align 4, !dbg !317
  br label %if.end26

if.end26:                                         ; preds = %land.end, %if.then15
  %40 = load i32, i32* %position, align 4, !dbg !318
  %idxprom27 = zext i32 %40 to i64, !dbg !319
  %41 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !319
  %rb_nodes28 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %41, i32 0, i32 0, !dbg !320
  %arrayidx29 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes28, i64 0, i64 %idxprom27, !dbg !319
  %42 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx29, align 8, !dbg !319
  %43 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !321
  %rb_nodes30 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %43, i32 0, i32 0, !dbg !322
  %arrayidx31 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes30, i64 0, i64 0, !dbg !321
  store %struct.archive_rb_node* %42, %struct.archive_rb_node** %arrayidx31, align 8, !dbg !323
  %44 = load i32, i32* %position, align 4, !dbg !324
  %idxprom32 = zext i32 %44 to i64, !dbg !325
  %45 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !325
  %rb_nodes33 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %45, i32 0, i32 0, !dbg !326
  %arrayidx34 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes33, i64 0, i64 %idxprom32, !dbg !325
  %46 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx34, align 8, !dbg !325
  %47 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !327
  %rb_nodes35 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %47, i32 0, i32 0, !dbg !328
  %arrayidx36 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes35, i64 0, i64 1, !dbg !327
  store %struct.archive_rb_node* %46, %struct.archive_rb_node** %arrayidx36, align 8, !dbg !329
  %48 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !330
  %49 = load i32, i32* %position, align 4, !dbg !331
  %idxprom37 = zext i32 %49 to i64, !dbg !332
  %50 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent, align 8, !dbg !332
  %rb_nodes38 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %50, i32 0, i32 0, !dbg !333
  %arrayidx39 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes38, i64 0, i64 %idxprom37, !dbg !332
  store %struct.archive_rb_node* %48, %struct.archive_rb_node** %arrayidx39, align 8, !dbg !334
  %51 = load i32, i32* %rebalance, align 4, !dbg !335
  %tobool40 = icmp ne i32 %51, 0, !dbg !335
  br i1 %tobool40, label %if.then41, label %if.end42, !dbg !337

if.then41:                                        ; preds = %if.end26
  %52 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !338
  %53 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !339
  call void @__archive_rb_tree_insert_rebalance(%struct.archive_rb_tree* %52, %struct.archive_rb_node* %53), !dbg !340
  br label %if.end42, !dbg !340

if.end42:                                         ; preds = %if.then41, %if.end26
  store i32 1, i32* %retval, align 4, !dbg !341
  br label %return, !dbg !341

return:                                           ; preds = %if.end42, %if.then
  %54 = load i32, i32* %retval, align 4, !dbg !342
  ret i32 %54, !dbg !342
}

; Function Attrs: nounwind uwtable
define internal void @__archive_rb_tree_insert_rebalance(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %self) #0 !dbg !64 {
entry:
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %father = alloca %struct.archive_rb_node*, align 8
  %grandpa = alloca %struct.archive_rb_node*, align 8
  %uncle = alloca %struct.archive_rb_node*, align 8
  %which = alloca i32, align 4
  %other = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !343, metadata !84), !dbg !344
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !345, metadata !84), !dbg !346
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %father, metadata !347, metadata !84), !dbg !348
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !349
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %0, i32 0, i32 1, !dbg !349
  %1 = load i64, i64* %rb_info, align 8, !dbg !349
  %and = and i64 %1, -4, !dbg !349
  %2 = inttoptr i64 %and to %struct.archive_rb_node*, !dbg !349
  store %struct.archive_rb_node* %2, %struct.archive_rb_node** %father, align 8, !dbg !348
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %grandpa, metadata !350, metadata !84), !dbg !351
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %uncle, metadata !352, metadata !84), !dbg !353
  call void @llvm.dbg.declare(metadata i32* %which, metadata !354, metadata !84), !dbg !355
  call void @llvm.dbg.declare(metadata i32* %other, metadata !356, metadata !84), !dbg !357
  br label %for.cond, !dbg !358

for.cond:                                         ; preds = %if.end30, %entry
  %3 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !359
  %rb_info1 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %3, i32 0, i32 1, !dbg !359
  %4 = load i64, i64* %rb_info1, align 8, !dbg !359
  %and2 = and i64 %4, -4, !dbg !359
  %5 = inttoptr i64 %and2 to %struct.archive_rb_node*, !dbg !359
  store %struct.archive_rb_node* %5, %struct.archive_rb_node** %grandpa, align 8, !dbg !363
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !364
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !365
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %7, i32 0, i32 0, !dbg !366
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 1, !dbg !365
  %8 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !365
  %cmp = icmp eq %struct.archive_rb_node* %6, %8, !dbg !367
  %conv = zext i1 %cmp to i32, !dbg !367
  store i32 %conv, i32* %which, align 4, !dbg !368
  %9 = load i32, i32* %which, align 4, !dbg !369
  %xor = xor i32 %9, 1, !dbg !370
  store i32 %xor, i32* %other, align 4, !dbg !371
  %10 = load i32, i32* %other, align 4, !dbg !372
  %idxprom = zext i32 %10 to i64, !dbg !373
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !373
  %rb_nodes3 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %11, i32 0, i32 0, !dbg !374
  %arrayidx4 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes3, i64 0, i64 %idxprom, !dbg !373
  %12 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx4, align 8, !dbg !373
  store %struct.archive_rb_node* %12, %struct.archive_rb_node** %uncle, align 8, !dbg !375
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %uncle, align 8, !dbg !376
  %cmp5 = icmp eq %struct.archive_rb_node* %13, null, !dbg !376
  br i1 %cmp5, label %if.then, label %lor.lhs.false, !dbg !376

lor.lhs.false:                                    ; preds = %for.cond
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %uncle, align 8, !dbg !378
  %rb_info7 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %14, i32 0, i32 1, !dbg !378
  %15 = load i64, i64* %rb_info7, align 8, !dbg !378
  %and8 = and i64 %15, 1, !dbg !378
  %cmp9 = icmp eq i64 %and8, 0, !dbg !378
  br i1 %cmp9, label %if.then, label %if.end, !dbg !378

if.then:                                          ; preds = %lor.lhs.false, %for.cond
  br label %for.end, !dbg !380

if.end:                                           ; preds = %lor.lhs.false
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %uncle, align 8, !dbg !381
  %rb_info11 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %16, i32 0, i32 1, !dbg !381
  %17 = load i64, i64* %rb_info11, align 8, !dbg !381
  %and12 = and i64 %17, -2, !dbg !381
  store i64 %and12, i64* %rb_info11, align 8, !dbg !381
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !382
  %rb_info13 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %18, i32 0, i32 1, !dbg !382
  %19 = load i64, i64* %rb_info13, align 8, !dbg !382
  %and14 = and i64 %19, -2, !dbg !382
  store i64 %and14, i64* %rb_info13, align 8, !dbg !382
  %20 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !383
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %20, i32 0, i32 0, !dbg !383
  %21 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !383
  %22 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !383
  %cmp15 = icmp eq %struct.archive_rb_node* %21, %22, !dbg !383
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !385

if.then17:                                        ; preds = %if.end
  br label %return, !dbg !386

if.end18:                                         ; preds = %if.end
  %23 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !388
  %rb_info19 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %23, i32 0, i32 1, !dbg !388
  %24 = load i64, i64* %rb_info19, align 8, !dbg !388
  %or = or i64 %24, 1, !dbg !388
  store i64 %or, i64* %rb_info19, align 8, !dbg !388
  %25 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !389
  store %struct.archive_rb_node* %25, %struct.archive_rb_node** %self.addr, align 8, !dbg !390
  %26 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !391
  %rb_info20 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %26, i32 0, i32 1, !dbg !391
  %27 = load i64, i64* %rb_info20, align 8, !dbg !391
  %and21 = and i64 %27, -4, !dbg !391
  %28 = inttoptr i64 %and21 to %struct.archive_rb_node*, !dbg !391
  store %struct.archive_rb_node* %28, %struct.archive_rb_node** %father, align 8, !dbg !392
  %29 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !393
  %cmp22 = icmp eq %struct.archive_rb_node* %29, null, !dbg !393
  br i1 %cmp22, label %if.then29, label %lor.lhs.false24, !dbg !393

lor.lhs.false24:                                  ; preds = %if.end18
  %30 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !395
  %rb_info25 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %30, i32 0, i32 1, !dbg !395
  %31 = load i64, i64* %rb_info25, align 8, !dbg !395
  %and26 = and i64 %31, 1, !dbg !395
  %cmp27 = icmp eq i64 %and26, 0, !dbg !395
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !395

if.then29:                                        ; preds = %lor.lhs.false24, %if.end18
  br label %return, !dbg !397

if.end30:                                         ; preds = %lor.lhs.false24
  br label %for.cond, !dbg !399

for.end:                                          ; preds = %if.then
  %32 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !401
  %33 = load i32, i32* %other, align 4, !dbg !403
  %idxprom31 = zext i32 %33 to i64, !dbg !404
  %34 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !404
  %rb_nodes32 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %34, i32 0, i32 0, !dbg !405
  %arrayidx33 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes32, i64 0, i64 %idxprom31, !dbg !404
  %35 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx33, align 8, !dbg !404
  %cmp34 = icmp eq %struct.archive_rb_node* %32, %35, !dbg !406
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !407

if.then36:                                        ; preds = %for.end
  %36 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !408
  %37 = load i32, i32* %other, align 4, !dbg !410
  call void @__archive_rb_tree_reparent_nodes(%struct.archive_rb_node* %36, i32 %37), !dbg !411
  br label %if.end37, !dbg !412

if.end37:                                         ; preds = %if.then36, %for.end
  %38 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !413
  %39 = load i32, i32* %which, align 4, !dbg !414
  call void @__archive_rb_tree_reparent_nodes(%struct.archive_rb_node* %38, i32 %39), !dbg !415
  %40 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !416
  %rbt_root38 = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %40, i32 0, i32 0, !dbg !416
  %41 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root38, align 8, !dbg !416
  %rb_info39 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %41, i32 0, i32 1, !dbg !416
  %42 = load i64, i64* %rb_info39, align 8, !dbg !416
  %and40 = and i64 %42, -2, !dbg !416
  store i64 %and40, i64* %rb_info39, align 8, !dbg !416
  br label %return, !dbg !417

return:                                           ; preds = %if.end37, %if.then29, %if.then17
  ret void, !dbg !418
}

; Function Attrs: nounwind uwtable
define void @__archive_rb_tree_remove_node(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %self) #0 !dbg !57 {
entry:
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %standin = alloca %struct.archive_rb_node*, align 8
  %which = alloca i32, align 4
  %rebalance = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !420, metadata !84), !dbg !421
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !422, metadata !84), !dbg !423
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %standin, metadata !424, metadata !84), !dbg !425
  call void @llvm.dbg.declare(metadata i32* %which, metadata !426, metadata !84), !dbg !427
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !428
  %cmp = icmp eq %struct.archive_rb_node* %0, null, !dbg !428
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !428

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !430
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %1, i32 0, i32 0, !dbg !430
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 0, !dbg !430
  %2 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !430
  %cmp1 = icmp eq %struct.archive_rb_node* %2, null, !dbg !430
  br i1 %cmp1, label %land.lhs.true, label %if.end, !dbg !430

land.lhs.true:                                    ; preds = %lor.lhs.false
  %3 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !432
  %rb_nodes2 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %3, i32 0, i32 0, !dbg !432
  %arrayidx3 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes2, i64 0, i64 1, !dbg !432
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx3, align 8, !dbg !432
  %cmp4 = icmp eq %struct.archive_rb_node* %4, null, !dbg !432
  br i1 %cmp4, label %if.then, label %if.end, !dbg !432

if.then:                                          ; preds = %land.lhs.true, %entry
  call void @llvm.dbg.declare(metadata i32* %rebalance, metadata !434, metadata !84), !dbg !436
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !437
  %cmp5 = icmp eq %struct.archive_rb_node* %5, null, !dbg !437
  br i1 %cmp5, label %land.rhs, label %lor.lhs.false6, !dbg !437

lor.lhs.false6:                                   ; preds = %if.then
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !438
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %6, i32 0, i32 1, !dbg !438
  %7 = load i64, i64* %rb_info, align 8, !dbg !438
  %and = and i64 %7, 1, !dbg !438
  %cmp7 = icmp eq i64 %and, 0, !dbg !438
  br i1 %cmp7, label %land.rhs, label %land.end, !dbg !440

land.rhs:                                         ; preds = %lor.lhs.false6, %if.then
  %8 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !441
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %8, i32 0, i32 0, !dbg !441
  %9 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !441
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !441
  %cmp8 = icmp eq %struct.archive_rb_node* %9, %10, !dbg !441
  %lnot = xor i1 %cmp8, true, !dbg !443
  br label %land.end

land.end:                                         ; preds = %land.rhs, %lor.lhs.false6
  %11 = phi i1 [ false, %lor.lhs.false6 ], [ %lnot, %land.rhs ]
  %land.ext = zext i1 %11 to i32, !dbg !444
  store i32 %land.ext, i32* %rebalance, align 4, !dbg !446
  %12 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !447
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !448
  %14 = load i32, i32* %rebalance, align 4, !dbg !449
  call void @__archive_rb_tree_prune_node(%struct.archive_rb_tree* %12, %struct.archive_rb_node* %13, i32 %14), !dbg !450
  br label %return, !dbg !451

if.end:                                           ; preds = %land.lhs.true, %lor.lhs.false
  %15 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !452
  %cmp9 = icmp eq %struct.archive_rb_node* %15, null, !dbg !452
  br i1 %cmp9, label %if.then18, label %land.lhs.true10, !dbg !452

land.lhs.true10:                                  ; preds = %if.end
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !454
  %rb_nodes11 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %16, i32 0, i32 0, !dbg !454
  %arrayidx12 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes11, i64 0, i64 0, !dbg !454
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx12, align 8, !dbg !454
  %cmp13 = icmp eq %struct.archive_rb_node* %17, null, !dbg !454
  br i1 %cmp13, label %if.then18, label %land.lhs.true14, !dbg !454

land.lhs.true14:                                  ; preds = %land.lhs.true10
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !456
  %rb_nodes15 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %18, i32 0, i32 0, !dbg !456
  %arrayidx16 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes15, i64 0, i64 1, !dbg !456
  %19 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx16, align 8, !dbg !456
  %cmp17 = icmp eq %struct.archive_rb_node* %19, null, !dbg !456
  br i1 %cmp17, label %if.then18, label %if.end22, !dbg !458

if.then18:                                        ; preds = %land.lhs.true14, %land.lhs.true10, %if.end
  %20 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !459
  %rb_nodes19 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %20, i32 0, i32 0, !dbg !459
  %arrayidx20 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes19, i64 0, i64 0, !dbg !459
  %21 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx20, align 8, !dbg !459
  %cmp21 = icmp eq %struct.archive_rb_node* %21, null, !dbg !459
  %cond = select i1 %cmp21, i32 1, i32 0, !dbg !459
  store i32 %cond, i32* %which, align 4, !dbg !461
  %22 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !462
  %23 = load i32, i32* %which, align 4, !dbg !463
  call void @__archive_rb_tree_prune_blackred_branch(%struct.archive_rb_node* %22, i32 %23), !dbg !464
  br label %return, !dbg !465

if.end22:                                         ; preds = %land.lhs.true14
  %24 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !466
  %rb_info23 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %24, i32 0, i32 1, !dbg !466
  %25 = load i64, i64* %rb_info23, align 8, !dbg !466
  %and24 = and i64 %25, 2, !dbg !466
  %tobool = icmp ne i64 %and24, 0, !dbg !466
  %cond25 = select i1 %tobool, i32 1, i32 0, !dbg !466
  %xor = xor i32 %cond25, 1, !dbg !467
  store i32 %xor, i32* %which, align 4, !dbg !468
  %26 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !469
  %27 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !470
  %28 = load i32, i32* %which, align 4, !dbg !471
  %call = call %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %26, %struct.archive_rb_node* %27, i32 %28), !dbg !472
  store %struct.archive_rb_node* %call, %struct.archive_rb_node** %standin, align 8, !dbg !473
  %29 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !474
  %30 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !475
  %31 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin, align 8, !dbg !476
  call void @__archive_rb_tree_swap_prune_and_rebalance(%struct.archive_rb_tree* %29, %struct.archive_rb_node* %30, %struct.archive_rb_node* %31), !dbg !477
  br label %return, !dbg !478

return:                                           ; preds = %if.end22, %if.then18, %land.end
  ret void, !dbg !479
}

; Function Attrs: nounwind uwtable
define internal void @__archive_rb_tree_prune_node(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %self, i32 %rebalance) #0 !dbg !68 {
entry:
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %rebalance.addr = alloca i32, align 4
  %which = alloca i32, align 4
  %father = alloca %struct.archive_rb_node*, align 8
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !481, metadata !84), !dbg !482
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !483, metadata !84), !dbg !484
  store i32 %rebalance, i32* %rebalance.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rebalance.addr, metadata !485, metadata !84), !dbg !486
  call void @llvm.dbg.declare(metadata i32* %which, metadata !487, metadata !84), !dbg !488
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !489
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %0, i32 0, i32 1, !dbg !489
  %1 = load i64, i64* %rb_info, align 8, !dbg !489
  %and = and i64 %1, 2, !dbg !489
  %tobool = icmp ne i64 %and, 0, !dbg !489
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !489
  store i32 %cond, i32* %which, align 4, !dbg !488
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %father, metadata !490, metadata !84), !dbg !491
  %2 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !492
  %rb_info1 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %2, i32 0, i32 1, !dbg !492
  %3 = load i64, i64* %rb_info1, align 8, !dbg !492
  %and2 = and i64 %3, -4, !dbg !492
  %4 = inttoptr i64 %and2 to %struct.archive_rb_node*, !dbg !492
  store %struct.archive_rb_node* %4, %struct.archive_rb_node** %father, align 8, !dbg !491
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !493
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %5, i32 0, i32 0, !dbg !494
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 0, !dbg !493
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !493
  %7 = load i32, i32* %which, align 4, !dbg !495
  %idxprom = zext i32 %7 to i64, !dbg !496
  %8 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !496
  %rb_nodes3 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %8, i32 0, i32 0, !dbg !497
  %arrayidx4 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes3, i64 0, i64 %idxprom, !dbg !496
  store %struct.archive_rb_node* %6, %struct.archive_rb_node** %arrayidx4, align 8, !dbg !498
  %9 = load i32, i32* %rebalance.addr, align 4, !dbg !499
  %tobool5 = icmp ne i32 %9, 0, !dbg !499
  br i1 %tobool5, label %if.then, label %if.end, !dbg !501

if.then:                                          ; preds = %entry
  %10 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !502
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !503
  %12 = load i32, i32* %which, align 4, !dbg !504
  call void @__archive_rb_tree_removal_rebalance(%struct.archive_rb_tree* %10, %struct.archive_rb_node* %11, i32 %12), !dbg !505
  br label %if.end, !dbg !505

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !506
}

; Function Attrs: nounwind uwtable
define internal void @__archive_rb_tree_prune_blackred_branch(%struct.archive_rb_node* %self, i32 %which) #0 !dbg !74 {
entry:
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %which.addr = alloca i32, align 4
  %father = alloca %struct.archive_rb_node*, align 8
  %son = alloca %struct.archive_rb_node*, align 8
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !507, metadata !84), !dbg !508
  store i32 %which, i32* %which.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %which.addr, metadata !509, metadata !84), !dbg !510
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %father, metadata !511, metadata !84), !dbg !512
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !513
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %0, i32 0, i32 1, !dbg !513
  %1 = load i64, i64* %rb_info, align 8, !dbg !513
  %and = and i64 %1, -4, !dbg !513
  %2 = inttoptr i64 %and to %struct.archive_rb_node*, !dbg !513
  store %struct.archive_rb_node* %2, %struct.archive_rb_node** %father, align 8, !dbg !512
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %son, metadata !514, metadata !84), !dbg !515
  %3 = load i32, i32* %which.addr, align 4, !dbg !516
  %idxprom = zext i32 %3 to i64, !dbg !517
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !517
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %4, i32 0, i32 0, !dbg !518
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !517
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !517
  store %struct.archive_rb_node* %5, %struct.archive_rb_node** %son, align 8, !dbg !515
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %son, align 8, !dbg !519
  %rb_info1 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %6, i32 0, i32 1, !dbg !519
  %7 = load i64, i64* %rb_info1, align 8, !dbg !519
  %8 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !519
  %rb_info2 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %8, i32 0, i32 1, !dbg !519
  %9 = load i64, i64* %rb_info2, align 8, !dbg !519
  %xor = xor i64 %7, %9, !dbg !519
  %and3 = and i64 %xor, 3, !dbg !519
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %son, align 8, !dbg !519
  %rb_info4 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %10, i32 0, i32 1, !dbg !519
  %11 = load i64, i64* %rb_info4, align 8, !dbg !519
  %xor5 = xor i64 %11, %and3, !dbg !519
  store i64 %xor5, i64* %rb_info4, align 8, !dbg !519
  %12 = load %struct.archive_rb_node*, %struct.archive_rb_node** %son, align 8, !dbg !520
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %son, align 8, !dbg !521
  %rb_info6 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %13, i32 0, i32 1, !dbg !521
  %14 = load i64, i64* %rb_info6, align 8, !dbg !521
  %and7 = and i64 %14, 2, !dbg !521
  %tobool = icmp ne i64 %and7, 0, !dbg !521
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !521
  %idxprom8 = sext i32 %cond to i64, !dbg !522
  %15 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !522
  %rb_nodes9 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %15, i32 0, i32 0, !dbg !523
  %arrayidx10 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes9, i64 0, i64 %idxprom8, !dbg !522
  store %struct.archive_rb_node* %12, %struct.archive_rb_node** %arrayidx10, align 8, !dbg !524
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %father, align 8, !dbg !525
  %17 = ptrtoint %struct.archive_rb_node* %16 to i64, !dbg !525
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %son, align 8, !dbg !525
  %rb_info11 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %18, i32 0, i32 1, !dbg !525
  %19 = load i64, i64* %rb_info11, align 8, !dbg !525
  %and12 = and i64 %19, 3, !dbg !525
  %or = or i64 %17, %and12, !dbg !525
  %20 = load %struct.archive_rb_node*, %struct.archive_rb_node** %son, align 8, !dbg !525
  %rb_info13 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %20, i32 0, i32 1, !dbg !525
  store i64 %or, i64* %rb_info13, align 8, !dbg !525
  ret void, !dbg !526
}

; Function Attrs: nounwind uwtable
define %struct.archive_rb_node* @__archive_rb_tree_iterate(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %self, i32 %direction) #0 !dbg !60 {
entry:
  %retval = alloca %struct.archive_rb_node*, align 8
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %direction.addr = alloca i32, align 4
  %other = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !527, metadata !84), !dbg !528
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !529, metadata !84), !dbg !530
  store i32 %direction, i32* %direction.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %direction.addr, metadata !531, metadata !84), !dbg !532
  call void @llvm.dbg.declare(metadata i32* %other, metadata !533, metadata !84), !dbg !534
  %0 = load i32, i32* %direction.addr, align 4, !dbg !535
  %xor = xor i32 %0, 1, !dbg !536
  store i32 %xor, i32* %other, align 4, !dbg !534
  %1 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !537
  %cmp = icmp eq %struct.archive_rb_node* %1, null, !dbg !539
  br i1 %cmp, label %if.then, label %if.end7, !dbg !540

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !541
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %2, i32 0, i32 0, !dbg !543
  %3 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !543
  store %struct.archive_rb_node* %3, %struct.archive_rb_node** %self.addr, align 8, !dbg !544
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !545
  %cmp1 = icmp eq %struct.archive_rb_node* %4, null, !dbg !545
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !547

if.then2:                                         ; preds = %if.then
  store %struct.archive_rb_node* null, %struct.archive_rb_node** %retval, align 8, !dbg !548
  br label %return, !dbg !548

if.end:                                           ; preds = %if.then
  br label %while.cond, !dbg !549

while.cond:                                       ; preds = %while.body, %if.end
  %5 = load i32, i32* %direction.addr, align 4, !dbg !550
  %idxprom = zext i32 %5 to i64, !dbg !550
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !550
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %6, i32 0, i32 0, !dbg !550
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !550
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !550
  %cmp3 = icmp eq %struct.archive_rb_node* %7, null, !dbg !550
  %lnot = xor i1 %cmp3, true, !dbg !552
  br i1 %lnot, label %while.body, label %while.end, !dbg !553

while.body:                                       ; preds = %while.cond
  %8 = load i32, i32* %direction.addr, align 4, !dbg !554
  %idxprom4 = zext i32 %8 to i64, !dbg !555
  %9 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !555
  %rb_nodes5 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %9, i32 0, i32 0, !dbg !556
  %arrayidx6 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes5, i64 0, i64 %idxprom4, !dbg !555
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx6, align 8, !dbg !555
  store %struct.archive_rb_node* %10, %struct.archive_rb_node** %self.addr, align 8, !dbg !557
  br label %while.cond, !dbg !558

while.end:                                        ; preds = %while.cond
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !560
  store %struct.archive_rb_node* %11, %struct.archive_rb_node** %retval, align 8, !dbg !561
  br label %return, !dbg !561

if.end7:                                          ; preds = %entry
  %12 = load i32, i32* %direction.addr, align 4, !dbg !562
  %idxprom8 = zext i32 %12 to i64, !dbg !562
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !562
  %rb_nodes9 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %13, i32 0, i32 0, !dbg !562
  %arrayidx10 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes9, i64 0, i64 %idxprom8, !dbg !562
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx10, align 8, !dbg !562
  %cmp11 = icmp eq %struct.archive_rb_node* %14, null, !dbg !562
  br i1 %cmp11, label %if.then12, label %if.end26, !dbg !564

if.then12:                                        ; preds = %if.end7
  br label %while.cond13, !dbg !565

while.cond13:                                     ; preds = %if.end22, %if.then12
  %15 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !567
  %rbt_root14 = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %15, i32 0, i32 0, !dbg !567
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root14, align 8, !dbg !567
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !567
  %cmp15 = icmp eq %struct.archive_rb_node* %16, %17, !dbg !567
  %lnot16 = xor i1 %cmp15, true, !dbg !569
  br i1 %lnot16, label %while.body17, label %while.end25, !dbg !570

while.body17:                                     ; preds = %while.cond13
  %18 = load i32, i32* %other, align 4, !dbg !571
  %19 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !574
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %19, i32 0, i32 1, !dbg !574
  %20 = load i64, i64* %rb_info, align 8, !dbg !574
  %and = and i64 %20, 2, !dbg !574
  %tobool = icmp ne i64 %and, 0, !dbg !574
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !574
  %cmp18 = icmp eq i32 %18, %cond, !dbg !575
  br i1 %cmp18, label %if.then19, label %if.end22, !dbg !576

if.then19:                                        ; preds = %while.body17
  %21 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !577
  %rb_info20 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %21, i32 0, i32 1, !dbg !577
  %22 = load i64, i64* %rb_info20, align 8, !dbg !577
  %and21 = and i64 %22, -4, !dbg !577
  %23 = inttoptr i64 %and21 to %struct.archive_rb_node*, !dbg !577
  store %struct.archive_rb_node* %23, %struct.archive_rb_node** %retval, align 8, !dbg !578
  br label %return, !dbg !578

if.end22:                                         ; preds = %while.body17
  %24 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !579
  %rb_info23 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %24, i32 0, i32 1, !dbg !579
  %25 = load i64, i64* %rb_info23, align 8, !dbg !579
  %and24 = and i64 %25, -4, !dbg !579
  %26 = inttoptr i64 %and24 to %struct.archive_rb_node*, !dbg !579
  store %struct.archive_rb_node* %26, %struct.archive_rb_node** %self.addr, align 8, !dbg !580
  br label %while.cond13, !dbg !581

while.end25:                                      ; preds = %while.cond13
  store %struct.archive_rb_node* null, %struct.archive_rb_node** %retval, align 8, !dbg !583
  br label %return, !dbg !583

if.end26:                                         ; preds = %if.end7
  %27 = load i32, i32* %direction.addr, align 4, !dbg !584
  %idxprom27 = zext i32 %27 to i64, !dbg !585
  %28 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !585
  %rb_nodes28 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %28, i32 0, i32 0, !dbg !586
  %arrayidx29 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes28, i64 0, i64 %idxprom27, !dbg !585
  %29 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx29, align 8, !dbg !585
  store %struct.archive_rb_node* %29, %struct.archive_rb_node** %self.addr, align 8, !dbg !587
  br label %while.cond30, !dbg !588

while.cond30:                                     ; preds = %while.body36, %if.end26
  %30 = load i32, i32* %other, align 4, !dbg !589
  %idxprom31 = zext i32 %30 to i64, !dbg !589
  %31 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !589
  %rb_nodes32 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %31, i32 0, i32 0, !dbg !589
  %arrayidx33 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes32, i64 0, i64 %idxprom31, !dbg !589
  %32 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx33, align 8, !dbg !589
  %cmp34 = icmp eq %struct.archive_rb_node* %32, null, !dbg !589
  %lnot35 = xor i1 %cmp34, true, !dbg !591
  br i1 %lnot35, label %while.body36, label %while.end40, !dbg !592

while.body36:                                     ; preds = %while.cond30
  %33 = load i32, i32* %other, align 4, !dbg !593
  %idxprom37 = zext i32 %33 to i64, !dbg !594
  %34 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !594
  %rb_nodes38 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %34, i32 0, i32 0, !dbg !595
  %arrayidx39 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes38, i64 0, i64 %idxprom37, !dbg !594
  %35 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx39, align 8, !dbg !594
  store %struct.archive_rb_node* %35, %struct.archive_rb_node** %self.addr, align 8, !dbg !596
  br label %while.cond30, !dbg !597

while.end40:                                      ; preds = %while.cond30
  %36 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !599
  store %struct.archive_rb_node* %36, %struct.archive_rb_node** %retval, align 8, !dbg !600
  br label %return, !dbg !600

return:                                           ; preds = %while.end40, %while.end25, %if.then19, %while.end, %if.then2
  %37 = load %struct.archive_rb_node*, %struct.archive_rb_node** %retval, align 8, !dbg !601
  ret %struct.archive_rb_node* %37, !dbg !601
}

; Function Attrs: nounwind uwtable
define internal void @__archive_rb_tree_swap_prune_and_rebalance(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %self, %struct.archive_rb_node* %standin) #0 !dbg !77 {
entry:
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %self.addr = alloca %struct.archive_rb_node*, align 8
  %standin.addr = alloca %struct.archive_rb_node*, align 8
  %standin_which = alloca i32, align 4
  %standin_other = alloca i32, align 4
  %standin_son = alloca %struct.archive_rb_node*, align 8
  %standin_father = alloca %struct.archive_rb_node*, align 8
  %rebalance = alloca i32, align 4
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !602, metadata !84), !dbg !603
  store %struct.archive_rb_node* %self, %struct.archive_rb_node** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %self.addr, metadata !604, metadata !84), !dbg !605
  store %struct.archive_rb_node* %standin, %struct.archive_rb_node** %standin.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %standin.addr, metadata !606, metadata !84), !dbg !607
  call void @llvm.dbg.declare(metadata i32* %standin_which, metadata !608, metadata !84), !dbg !609
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !610
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %0, i32 0, i32 1, !dbg !610
  %1 = load i64, i64* %rb_info, align 8, !dbg !610
  %and = and i64 %1, 2, !dbg !610
  %tobool = icmp ne i64 %and, 0, !dbg !610
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !610
  store i32 %cond, i32* %standin_which, align 4, !dbg !609
  call void @llvm.dbg.declare(metadata i32* %standin_other, metadata !611, metadata !84), !dbg !612
  %2 = load i32, i32* %standin_which, align 4, !dbg !613
  %xor = xor i32 %2, 1, !dbg !614
  store i32 %xor, i32* %standin_other, align 4, !dbg !612
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %standin_son, metadata !615, metadata !84), !dbg !616
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %standin_father, metadata !617, metadata !84), !dbg !618
  %3 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !619
  %rb_info1 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %3, i32 0, i32 1, !dbg !619
  %4 = load i64, i64* %rb_info1, align 8, !dbg !619
  %and2 = and i64 %4, -4, !dbg !619
  %5 = inttoptr i64 %and2 to %struct.archive_rb_node*, !dbg !619
  store %struct.archive_rb_node* %5, %struct.archive_rb_node** %standin_father, align 8, !dbg !618
  call void @llvm.dbg.declare(metadata i32* %rebalance, metadata !620, metadata !84), !dbg !621
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !622
  %cmp = icmp eq %struct.archive_rb_node* %6, null, !dbg !622
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !622

lor.rhs:                                          ; preds = %entry
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !623
  %rb_info3 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %7, i32 0, i32 1, !dbg !623
  %8 = load i64, i64* %rb_info3, align 8, !dbg !623
  %and4 = and i64 %8, 1, !dbg !623
  %cmp5 = icmp eq i64 %and4, 0, !dbg !623
  br label %lor.end, !dbg !623

lor.end:                                          ; preds = %lor.rhs, %entry
  %9 = phi i1 [ true, %entry ], [ %cmp5, %lor.rhs ]
  %lor.ext = zext i1 %9 to i32, !dbg !625
  store i32 %lor.ext, i32* %rebalance, align 4, !dbg !627
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_father, align 8, !dbg !628
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !630
  %cmp6 = icmp eq %struct.archive_rb_node* %10, %11, !dbg !631
  br i1 %cmp6, label %if.then, label %if.else, !dbg !632

if.then:                                          ; preds = %lor.end
  %12 = load i32, i32* %standin_which, align 4, !dbg !633
  %idxprom = zext i32 %12 to i64, !dbg !635
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !635
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %13, i32 0, i32 0, !dbg !636
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !635
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !635
  store %struct.archive_rb_node* %14, %struct.archive_rb_node** %standin_son, align 8, !dbg !637
  br label %if.end, !dbg !638

if.else:                                          ; preds = %lor.end
  %15 = load i32, i32* %standin_other, align 4, !dbg !639
  %idxprom7 = zext i32 %15 to i64, !dbg !641
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !641
  %rb_nodes8 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %16, i32 0, i32 0, !dbg !642
  %arrayidx9 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes8, i64 0, i64 %idxprom7, !dbg !641
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx9, align 8, !dbg !641
  store %struct.archive_rb_node* %17, %struct.archive_rb_node** %standin_son, align 8, !dbg !643
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !644
  %cmp10 = icmp eq %struct.archive_rb_node* %18, null, !dbg !644
  br i1 %cmp10, label %if.end29, label %land.lhs.true, !dbg !644

land.lhs.true:                                    ; preds = %if.end
  %19 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !646
  %rb_info11 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %19, i32 0, i32 1, !dbg !646
  %20 = load i64, i64* %rb_info11, align 8, !dbg !646
  %and12 = and i64 %20, 1, !dbg !646
  %cmp13 = icmp ne i64 %and12, 0, !dbg !646
  br i1 %cmp13, label %if.then14, label %if.end29, !dbg !646

if.then14:                                        ; preds = %land.lhs.true
  %21 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !648
  %rb_info15 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %21, i32 0, i32 1, !dbg !648
  %22 = load i64, i64* %rb_info15, align 8, !dbg !648
  %and16 = and i64 %22, -2, !dbg !648
  store i64 %and16, i64* %rb_info15, align 8, !dbg !648
  store i32 0, i32* %rebalance, align 4, !dbg !650
  %23 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_father, align 8, !dbg !651
  %24 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !653
  %cmp17 = icmp ne %struct.archive_rb_node* %23, %24, !dbg !654
  br i1 %cmp17, label %if.then18, label %if.end28, !dbg !655

if.then18:                                        ; preds = %if.then14
  %25 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_father, align 8, !dbg !656
  %26 = ptrtoint %struct.archive_rb_node* %25 to i64, !dbg !656
  %27 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !656
  %rb_info19 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %27, i32 0, i32 1, !dbg !656
  %28 = load i64, i64* %rb_info19, align 8, !dbg !656
  %and20 = and i64 %28, 3, !dbg !656
  %or = or i64 %26, %and20, !dbg !656
  %29 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !656
  %rb_info21 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %29, i32 0, i32 1, !dbg !656
  store i64 %or, i64* %rb_info21, align 8, !dbg !656
  %30 = load i32, i32* %standin_which, align 4, !dbg !658
  %tobool22 = icmp ne i32 %30, 0, !dbg !658
  br i1 %tobool22, label %cond.true, label %cond.false, !dbg !658

cond.true:                                        ; preds = %if.then18
  %31 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !659
  %rb_info23 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %31, i32 0, i32 1, !dbg !659
  %32 = load i64, i64* %rb_info23, align 8, !dbg !659
  %or24 = or i64 %32, 2, !dbg !659
  store i64 %or24, i64* %rb_info23, align 8, !dbg !659
  br label %cond.end, !dbg !659

cond.false:                                       ; preds = %if.then18
  %33 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !661
  %rb_info25 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %33, i32 0, i32 1, !dbg !661
  %34 = load i64, i64* %rb_info25, align 8, !dbg !661
  %and26 = and i64 %34, -3, !dbg !661
  store i64 %and26, i64* %rb_info25, align 8, !dbg !661
  br label %cond.end, !dbg !661

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond27 = phi i64 [ %or24, %cond.true ], [ %and26, %cond.false ], !dbg !663
  br label %if.end28, !dbg !665

if.end28:                                         ; preds = %cond.end, %if.then14
  br label %if.end29, !dbg !666

if.end29:                                         ; preds = %if.end28, %land.lhs.true, %if.end
  %35 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_father, align 8, !dbg !667
  %36 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !669
  %cmp30 = icmp eq %struct.archive_rb_node* %35, %36, !dbg !670
  br i1 %cmp30, label %if.then31, label %if.else32, !dbg !671

if.then31:                                        ; preds = %if.end29
  %37 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !672
  store %struct.archive_rb_node* %37, %struct.archive_rb_node** %standin_father, align 8, !dbg !674
  br label %if.end52, !dbg !675

if.else32:                                        ; preds = %if.end29
  %38 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_son, align 8, !dbg !676
  %39 = load i32, i32* %standin_which, align 4, !dbg !678
  %idxprom33 = zext i32 %39 to i64, !dbg !679
  %40 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_father, align 8, !dbg !679
  %rb_nodes34 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %40, i32 0, i32 0, !dbg !680
  %arrayidx35 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes34, i64 0, i64 %idxprom33, !dbg !679
  store %struct.archive_rb_node* %38, %struct.archive_rb_node** %arrayidx35, align 8, !dbg !681
  %41 = load i32, i32* %standin_other, align 4, !dbg !682
  %idxprom36 = zext i32 %41 to i64, !dbg !683
  %42 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !683
  %rb_nodes37 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %42, i32 0, i32 0, !dbg !684
  %arrayidx38 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes37, i64 0, i64 %idxprom36, !dbg !683
  %43 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx38, align 8, !dbg !683
  %44 = load i32, i32* %standin_other, align 4, !dbg !685
  %idxprom39 = zext i32 %44 to i64, !dbg !686
  %45 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !686
  %rb_nodes40 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %45, i32 0, i32 0, !dbg !687
  %arrayidx41 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes40, i64 0, i64 %idxprom39, !dbg !686
  store %struct.archive_rb_node* %43, %struct.archive_rb_node** %arrayidx41, align 8, !dbg !688
  %46 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !689
  %47 = ptrtoint %struct.archive_rb_node* %46 to i64, !dbg !689
  %48 = load i32, i32* %standin_other, align 4, !dbg !689
  %idxprom42 = zext i32 %48 to i64, !dbg !689
  %49 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !689
  %rb_nodes43 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %49, i32 0, i32 0, !dbg !689
  %arrayidx44 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes43, i64 0, i64 %idxprom42, !dbg !689
  %50 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx44, align 8, !dbg !689
  %rb_info45 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %50, i32 0, i32 1, !dbg !689
  %51 = load i64, i64* %rb_info45, align 8, !dbg !689
  %and46 = and i64 %51, 3, !dbg !689
  %or47 = or i64 %47, %and46, !dbg !689
  %52 = load i32, i32* %standin_other, align 4, !dbg !689
  %idxprom48 = zext i32 %52 to i64, !dbg !689
  %53 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !689
  %rb_nodes49 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %53, i32 0, i32 0, !dbg !689
  %arrayidx50 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes49, i64 0, i64 %idxprom48, !dbg !689
  %54 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx50, align 8, !dbg !689
  %rb_info51 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %54, i32 0, i32 1, !dbg !689
  store i64 %or47, i64* %rb_info51, align 8, !dbg !689
  %55 = load i32, i32* %standin_which, align 4, !dbg !690
  store i32 %55, i32* %standin_other, align 4, !dbg !691
  br label %if.end52

if.end52:                                         ; preds = %if.else32, %if.then31
  %56 = load i32, i32* %standin_other, align 4, !dbg !692
  %idxprom53 = zext i32 %56 to i64, !dbg !693
  %57 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !693
  %rb_nodes54 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %57, i32 0, i32 0, !dbg !694
  %arrayidx55 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes54, i64 0, i64 %idxprom53, !dbg !693
  %58 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx55, align 8, !dbg !693
  %59 = load i32, i32* %standin_other, align 4, !dbg !695
  %idxprom56 = zext i32 %59 to i64, !dbg !696
  %60 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !696
  %rb_nodes57 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %60, i32 0, i32 0, !dbg !697
  %arrayidx58 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes57, i64 0, i64 %idxprom56, !dbg !696
  store %struct.archive_rb_node* %58, %struct.archive_rb_node** %arrayidx58, align 8, !dbg !698
  %61 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !699
  %62 = ptrtoint %struct.archive_rb_node* %61 to i64, !dbg !699
  %63 = load i32, i32* %standin_other, align 4, !dbg !699
  %idxprom59 = zext i32 %63 to i64, !dbg !699
  %64 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !699
  %rb_nodes60 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %64, i32 0, i32 0, !dbg !699
  %arrayidx61 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes60, i64 0, i64 %idxprom59, !dbg !699
  %65 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx61, align 8, !dbg !699
  %rb_info62 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %65, i32 0, i32 1, !dbg !699
  %66 = load i64, i64* %rb_info62, align 8, !dbg !699
  %and63 = and i64 %66, 3, !dbg !699
  %or64 = or i64 %62, %and63, !dbg !699
  %67 = load i32, i32* %standin_other, align 4, !dbg !699
  %idxprom65 = zext i32 %67 to i64, !dbg !699
  %68 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !699
  %rb_nodes66 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %68, i32 0, i32 0, !dbg !699
  %arrayidx67 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes66, i64 0, i64 %idxprom65, !dbg !699
  %69 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx67, align 8, !dbg !699
  %rb_info68 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %69, i32 0, i32 1, !dbg !699
  store i64 %or64, i64* %rb_info68, align 8, !dbg !699
  %70 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !700
  %rb_info69 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %70, i32 0, i32 1, !dbg !700
  %71 = load i64, i64* %rb_info69, align 8, !dbg !700
  %72 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !700
  %rb_info70 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %72, i32 0, i32 1, !dbg !700
  %73 = load i64, i64* %rb_info70, align 8, !dbg !700
  %xor71 = xor i64 %71, %73, !dbg !700
  %and72 = and i64 %xor71, 3, !dbg !700
  %74 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !700
  %rb_info73 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %74, i32 0, i32 1, !dbg !700
  %75 = load i64, i64* %rb_info73, align 8, !dbg !700
  %xor74 = xor i64 %75, %and72, !dbg !700
  store i64 %xor74, i64* %rb_info73, align 8, !dbg !700
  %76 = load %struct.archive_rb_node*, %struct.archive_rb_node** %self.addr, align 8, !dbg !701
  %rb_info75 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %76, i32 0, i32 1, !dbg !701
  %77 = load i64, i64* %rb_info75, align 8, !dbg !701
  %and76 = and i64 %77, -4, !dbg !701
  %78 = inttoptr i64 %and76 to %struct.archive_rb_node*, !dbg !701
  %79 = ptrtoint %struct.archive_rb_node* %78 to i64, !dbg !701
  %80 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !701
  %rb_info77 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %80, i32 0, i32 1, !dbg !701
  %81 = load i64, i64* %rb_info77, align 8, !dbg !701
  %and78 = and i64 %81, 3, !dbg !701
  %or79 = or i64 %79, %and78, !dbg !701
  %82 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !701
  %rb_info80 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %82, i32 0, i32 1, !dbg !701
  store i64 %or79, i64* %rb_info80, align 8, !dbg !701
  %83 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !702
  %84 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !703
  %rb_info81 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %84, i32 0, i32 1, !dbg !703
  %85 = load i64, i64* %rb_info81, align 8, !dbg !703
  %and82 = and i64 %85, 2, !dbg !703
  %tobool83 = icmp ne i64 %and82, 0, !dbg !703
  %cond84 = select i1 %tobool83, i32 1, i32 0, !dbg !703
  %idxprom85 = sext i32 %cond84 to i64, !dbg !704
  %86 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin.addr, align 8, !dbg !704
  %rb_info86 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %86, i32 0, i32 1, !dbg !704
  %87 = load i64, i64* %rb_info86, align 8, !dbg !704
  %and87 = and i64 %87, -4, !dbg !704
  %88 = inttoptr i64 %and87 to %struct.archive_rb_node*, !dbg !704
  %rb_nodes88 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %88, i32 0, i32 0, !dbg !705
  %arrayidx89 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes88, i64 0, i64 %idxprom85, !dbg !704
  store %struct.archive_rb_node* %83, %struct.archive_rb_node** %arrayidx89, align 8, !dbg !706
  %89 = load i32, i32* %rebalance, align 4, !dbg !707
  %tobool90 = icmp ne i32 %89, 0, !dbg !707
  br i1 %tobool90, label %if.then91, label %if.end92, !dbg !709

if.then91:                                        ; preds = %if.end52
  %90 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !710
  %91 = load %struct.archive_rb_node*, %struct.archive_rb_node** %standin_father, align 8, !dbg !711
  %92 = load i32, i32* %standin_which, align 4, !dbg !712
  call void @__archive_rb_tree_removal_rebalance(%struct.archive_rb_tree* %90, %struct.archive_rb_node* %91, i32 %92), !dbg !713
  br label %if.end92, !dbg !713

if.end92:                                         ; preds = %if.then91, %if.end52
  ret void, !dbg !714
}

; Function Attrs: nounwind uwtable
define internal void @__archive_rb_tree_reparent_nodes(%struct.archive_rb_node* %old_father, i32 %which) #0 !dbg !65 {
entry:
  %old_father.addr = alloca %struct.archive_rb_node*, align 8
  %which.addr = alloca i32, align 4
  %other = alloca i32, align 4
  %grandpa = alloca %struct.archive_rb_node*, align 8
  %old_child = alloca %struct.archive_rb_node*, align 8
  %new_father = alloca %struct.archive_rb_node*, align 8
  %new_child = alloca %struct.archive_rb_node*, align 8
  %xorinfo = alloca i64, align 8
  store %struct.archive_rb_node* %old_father, %struct.archive_rb_node** %old_father.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %old_father.addr, metadata !715, metadata !84), !dbg !716
  store i32 %which, i32* %which.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %which.addr, metadata !717, metadata !84), !dbg !718
  call void @llvm.dbg.declare(metadata i32* %other, metadata !719, metadata !84), !dbg !720
  %0 = load i32, i32* %which.addr, align 4, !dbg !721
  %xor = xor i32 %0, 1, !dbg !722
  store i32 %xor, i32* %other, align 4, !dbg !720
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %grandpa, metadata !723, metadata !84), !dbg !725
  %1 = load %struct.archive_rb_node*, %struct.archive_rb_node** %old_father.addr, align 8, !dbg !726
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %1, i32 0, i32 1, !dbg !726
  %2 = load i64, i64* %rb_info, align 8, !dbg !726
  %and = and i64 %2, -4, !dbg !726
  %3 = inttoptr i64 %and to %struct.archive_rb_node*, !dbg !726
  store %struct.archive_rb_node* %3, %struct.archive_rb_node** %grandpa, align 8, !dbg !725
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %old_child, metadata !727, metadata !84), !dbg !728
  %4 = load i32, i32* %which.addr, align 4, !dbg !729
  %idxprom = zext i32 %4 to i64, !dbg !730
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %old_father.addr, align 8, !dbg !730
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %5, i32 0, i32 0, !dbg !731
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !730
  %6 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !730
  store %struct.archive_rb_node* %6, %struct.archive_rb_node** %old_child, align 8, !dbg !728
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %new_father, metadata !732, metadata !84), !dbg !733
  %7 = load %struct.archive_rb_node*, %struct.archive_rb_node** %old_child, align 8, !dbg !734
  store %struct.archive_rb_node* %7, %struct.archive_rb_node** %new_father, align 8, !dbg !733
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %new_child, metadata !735, metadata !84), !dbg !736
  %8 = load %struct.archive_rb_node*, %struct.archive_rb_node** %old_father.addr, align 8, !dbg !737
  store %struct.archive_rb_node* %8, %struct.archive_rb_node** %new_child, align 8, !dbg !736
  %9 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !738
  %cmp = icmp eq %struct.archive_rb_node* %9, null, !dbg !740
  br i1 %cmp, label %if.then, label %if.end, !dbg !741

if.then:                                          ; preds = %entry
  br label %if.end66, !dbg !742

if.end:                                           ; preds = %entry
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !743
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %old_father.addr, align 8, !dbg !744
  %rb_info1 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %11, i32 0, i32 1, !dbg !744
  %12 = load i64, i64* %rb_info1, align 8, !dbg !744
  %and2 = and i64 %12, 2, !dbg !744
  %tobool = icmp ne i64 %and2, 0, !dbg !744
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !744
  %idxprom3 = sext i32 %cond to i64, !dbg !745
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !745
  %rb_nodes4 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %13, i32 0, i32 0, !dbg !746
  %arrayidx5 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes4, i64 0, i64 %idxprom3, !dbg !745
  store %struct.archive_rb_node* %10, %struct.archive_rb_node** %arrayidx5, align 8, !dbg !747
  %14 = load i32, i32* %other, align 4, !dbg !748
  %idxprom6 = zext i32 %14 to i64, !dbg !749
  %15 = load %struct.archive_rb_node*, %struct.archive_rb_node** %old_child, align 8, !dbg !749
  %rb_nodes7 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %15, i32 0, i32 0, !dbg !750
  %arrayidx8 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes7, i64 0, i64 %idxprom6, !dbg !749
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx8, align 8, !dbg !749
  %17 = load i32, i32* %which.addr, align 4, !dbg !751
  %idxprom9 = zext i32 %17 to i64, !dbg !752
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !752
  %rb_nodes10 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %18, i32 0, i32 0, !dbg !753
  %arrayidx11 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes10, i64 0, i64 %idxprom9, !dbg !752
  store %struct.archive_rb_node* %16, %struct.archive_rb_node** %arrayidx11, align 8, !dbg !754
  %19 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !755
  %20 = load i32, i32* %other, align 4, !dbg !756
  %idxprom12 = zext i32 %20 to i64, !dbg !757
  %21 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !757
  %rb_nodes13 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %21, i32 0, i32 0, !dbg !758
  %arrayidx14 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes13, i64 0, i64 %idxprom12, !dbg !757
  store %struct.archive_rb_node* %19, %struct.archive_rb_node** %arrayidx14, align 8, !dbg !759
  %22 = load %struct.archive_rb_node*, %struct.archive_rb_node** %grandpa, align 8, !dbg !760
  %23 = ptrtoint %struct.archive_rb_node* %22 to i64, !dbg !760
  %24 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !760
  %rb_info15 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %24, i32 0, i32 1, !dbg !760
  %25 = load i64, i64* %rb_info15, align 8, !dbg !760
  %and16 = and i64 %25, 3, !dbg !760
  %or = or i64 %23, %and16, !dbg !760
  %26 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !760
  %rb_info17 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %26, i32 0, i32 1, !dbg !760
  store i64 %or, i64* %rb_info17, align 8, !dbg !760
  %27 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !761
  %28 = ptrtoint %struct.archive_rb_node* %27 to i64, !dbg !761
  %29 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !761
  %rb_info18 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %29, i32 0, i32 1, !dbg !761
  %30 = load i64, i64* %rb_info18, align 8, !dbg !761
  %and19 = and i64 %30, 3, !dbg !761
  %or20 = or i64 %28, %and19, !dbg !761
  %31 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !761
  %rb_info21 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %31, i32 0, i32 1, !dbg !761
  store i64 %or20, i64* %rb_info21, align 8, !dbg !761
  br label %do.body, !dbg !762

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %xorinfo, metadata !763, metadata !84), !dbg !765
  %32 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !766
  %rb_info22 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %32, i32 0, i32 1, !dbg !766
  %33 = load i64, i64* %rb_info22, align 8, !dbg !766
  %34 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !766
  %rb_info23 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %34, i32 0, i32 1, !dbg !766
  %35 = load i64, i64* %rb_info23, align 8, !dbg !766
  %xor24 = xor i64 %33, %35, !dbg !766
  %and25 = and i64 %xor24, 3, !dbg !766
  store i64 %and25, i64* %xorinfo, align 8, !dbg !766
  %36 = load i64, i64* %xorinfo, align 8, !dbg !766
  %37 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_father, align 8, !dbg !766
  %rb_info26 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %37, i32 0, i32 1, !dbg !766
  %38 = load i64, i64* %rb_info26, align 8, !dbg !766
  %xor27 = xor i64 %38, %36, !dbg !766
  store i64 %xor27, i64* %rb_info26, align 8, !dbg !766
  %39 = load i64, i64* %xorinfo, align 8, !dbg !766
  %40 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !766
  %rb_info28 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %40, i32 0, i32 1, !dbg !766
  %41 = load i64, i64* %rb_info28, align 8, !dbg !766
  %xor29 = xor i64 %41, %39, !dbg !766
  store i64 %xor29, i64* %rb_info28, align 8, !dbg !766
  br label %do.end, !dbg !766

do.end:                                           ; preds = %do.body
  %42 = load i32, i32* %other, align 4, !dbg !768
  %tobool30 = icmp ne i32 %42, 0, !dbg !768
  br i1 %tobool30, label %cond.true, label %cond.false, !dbg !768

cond.true:                                        ; preds = %do.end
  %43 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !769
  %rb_info31 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %43, i32 0, i32 1, !dbg !769
  %44 = load i64, i64* %rb_info31, align 8, !dbg !769
  %or32 = or i64 %44, 2, !dbg !769
  store i64 %or32, i64* %rb_info31, align 8, !dbg !769
  br label %cond.end, !dbg !769

cond.false:                                       ; preds = %do.end
  %45 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !771
  %rb_info33 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %45, i32 0, i32 1, !dbg !771
  %46 = load i64, i64* %rb_info33, align 8, !dbg !771
  %and34 = and i64 %46, -3, !dbg !771
  store i64 %and34, i64* %rb_info33, align 8, !dbg !771
  br label %cond.end, !dbg !771

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond35 = phi i64 [ %or32, %cond.true ], [ %and34, %cond.false ], !dbg !773
  %47 = load i32, i32* %which.addr, align 4, !dbg !775
  %idxprom36 = zext i32 %47 to i64, !dbg !775
  %48 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !775
  %rb_nodes37 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %48, i32 0, i32 0, !dbg !775
  %arrayidx38 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes37, i64 0, i64 %idxprom36, !dbg !775
  %49 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx38, align 8, !dbg !775
  %cmp39 = icmp eq %struct.archive_rb_node* %49, null, !dbg !775
  br i1 %cmp39, label %if.end66, label %if.then40, !dbg !777

if.then40:                                        ; preds = %cond.end
  %50 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !778
  %51 = ptrtoint %struct.archive_rb_node* %50 to i64, !dbg !778
  %52 = load i32, i32* %which.addr, align 4, !dbg !778
  %idxprom41 = zext i32 %52 to i64, !dbg !778
  %53 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !778
  %rb_nodes42 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %53, i32 0, i32 0, !dbg !778
  %arrayidx43 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes42, i64 0, i64 %idxprom41, !dbg !778
  %54 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx43, align 8, !dbg !778
  %rb_info44 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %54, i32 0, i32 1, !dbg !778
  %55 = load i64, i64* %rb_info44, align 8, !dbg !778
  %and45 = and i64 %55, 3, !dbg !778
  %or46 = or i64 %51, %and45, !dbg !778
  %56 = load i32, i32* %which.addr, align 4, !dbg !778
  %idxprom47 = zext i32 %56 to i64, !dbg !778
  %57 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !778
  %rb_nodes48 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %57, i32 0, i32 0, !dbg !778
  %arrayidx49 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes48, i64 0, i64 %idxprom47, !dbg !778
  %58 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx49, align 8, !dbg !778
  %rb_info50 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %58, i32 0, i32 1, !dbg !778
  store i64 %or46, i64* %rb_info50, align 8, !dbg !778
  %59 = load i32, i32* %which.addr, align 4, !dbg !780
  %tobool51 = icmp ne i32 %59, 0, !dbg !780
  br i1 %tobool51, label %cond.true52, label %cond.false58, !dbg !780

cond.true52:                                      ; preds = %if.then40
  %60 = load i32, i32* %which.addr, align 4, !dbg !781
  %idxprom53 = zext i32 %60 to i64, !dbg !781
  %61 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !781
  %rb_nodes54 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %61, i32 0, i32 0, !dbg !781
  %arrayidx55 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes54, i64 0, i64 %idxprom53, !dbg !781
  %62 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx55, align 8, !dbg !781
  %rb_info56 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %62, i32 0, i32 1, !dbg !781
  %63 = load i64, i64* %rb_info56, align 8, !dbg !781
  %or57 = or i64 %63, 2, !dbg !781
  store i64 %or57, i64* %rb_info56, align 8, !dbg !781
  br label %cond.end64, !dbg !781

cond.false58:                                     ; preds = %if.then40
  %64 = load i32, i32* %which.addr, align 4, !dbg !783
  %idxprom59 = zext i32 %64 to i64, !dbg !783
  %65 = load %struct.archive_rb_node*, %struct.archive_rb_node** %new_child, align 8, !dbg !783
  %rb_nodes60 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %65, i32 0, i32 0, !dbg !783
  %arrayidx61 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes60, i64 0, i64 %idxprom59, !dbg !783
  %66 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx61, align 8, !dbg !783
  %rb_info62 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %66, i32 0, i32 1, !dbg !783
  %67 = load i64, i64* %rb_info62, align 8, !dbg !783
  %and63 = and i64 %67, -3, !dbg !783
  store i64 %and63, i64* %rb_info62, align 8, !dbg !783
  br label %cond.end64, !dbg !783

cond.end64:                                       ; preds = %cond.false58, %cond.true52
  %cond65 = phi i64 [ %or57, %cond.true52 ], [ %and63, %cond.false58 ], !dbg !785
  br label %if.end66, !dbg !787

if.end66:                                         ; preds = %if.then, %cond.end64, %cond.end
  ret void, !dbg !788
}

; Function Attrs: nounwind uwtable
define internal void @__archive_rb_tree_removal_rebalance(%struct.archive_rb_tree* %rbt, %struct.archive_rb_node* %parent, i32 %which) #0 !dbg !71 {
entry:
  %rbt.addr = alloca %struct.archive_rb_tree*, align 8
  %parent.addr = alloca %struct.archive_rb_node*, align 8
  %which.addr = alloca i32, align 4
  %other = alloca i32, align 4
  %brother = alloca %struct.archive_rb_node*, align 8
  store %struct.archive_rb_tree* %rbt, %struct.archive_rb_tree** %rbt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_tree** %rbt.addr, metadata !789, metadata !84), !dbg !790
  store %struct.archive_rb_node* %parent, %struct.archive_rb_node** %parent.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %parent.addr, metadata !791, metadata !84), !dbg !792
  store i32 %which, i32* %which.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %which.addr, metadata !793, metadata !84), !dbg !794
  br label %while.cond, !dbg !795

while.cond:                                       ; preds = %if.end48, %entry
  %0 = load i32, i32* %which.addr, align 4, !dbg !796
  %idxprom = zext i32 %0 to i64, !dbg !796
  %1 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !796
  %rb_nodes = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %1, i32 0, i32 0, !dbg !796
  %arrayidx = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes, i64 0, i64 %idxprom, !dbg !796
  %2 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx, align 8, !dbg !796
  %cmp = icmp eq %struct.archive_rb_node* %2, null, !dbg !796
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !796

lor.rhs:                                          ; preds = %while.cond
  %3 = load i32, i32* %which.addr, align 4, !dbg !798
  %idxprom1 = zext i32 %3 to i64, !dbg !798
  %4 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !798
  %rb_nodes2 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %4, i32 0, i32 0, !dbg !798
  %arrayidx3 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes2, i64 0, i64 %idxprom1, !dbg !798
  %5 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx3, align 8, !dbg !798
  %rb_info = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %5, i32 0, i32 1, !dbg !798
  %6 = load i64, i64* %rb_info, align 8, !dbg !798
  %and = and i64 %6, 1, !dbg !798
  %cmp4 = icmp eq i64 %and, 0, !dbg !798
  br label %lor.end, !dbg !798

lor.end:                                          ; preds = %lor.rhs, %while.cond
  %7 = phi i1 [ true, %while.cond ], [ %cmp4, %lor.rhs ]
  br i1 %7, label %while.body, label %while.end, !dbg !800

while.body:                                       ; preds = %lor.end
  call void @llvm.dbg.declare(metadata i32* %other, metadata !802, metadata !84), !dbg !804
  %8 = load i32, i32* %which.addr, align 4, !dbg !805
  %xor = xor i32 %8, 1, !dbg !806
  store i32 %xor, i32* %other, align 4, !dbg !804
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %brother, metadata !807, metadata !84), !dbg !808
  %9 = load i32, i32* %other, align 4, !dbg !809
  %idxprom5 = zext i32 %9 to i64, !dbg !810
  %10 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !810
  %rb_nodes6 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %10, i32 0, i32 0, !dbg !811
  %arrayidx7 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes6, i64 0, i64 %idxprom5, !dbg !810
  %11 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx7, align 8, !dbg !810
  store %struct.archive_rb_node* %11, %struct.archive_rb_node** %brother, align 8, !dbg !808
  %12 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !812
  %cmp8 = icmp eq %struct.archive_rb_node* %12, null, !dbg !814
  br i1 %cmp8, label %if.then, label %if.end, !dbg !815

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !816

if.end:                                           ; preds = %while.body
  %13 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !817
  %cmp9 = icmp eq %struct.archive_rb_node* %13, null, !dbg !817
  br i1 %cmp9, label %land.lhs.true, label %lor.lhs.false, !dbg !817

lor.lhs.false:                                    ; preds = %if.end
  %14 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !819
  %rb_info10 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %14, i32 0, i32 1, !dbg !819
  %15 = load i64, i64* %rb_info10, align 8, !dbg !819
  %and11 = and i64 %15, 1, !dbg !819
  %cmp12 = icmp eq i64 %and11, 0, !dbg !819
  br i1 %cmp12, label %land.lhs.true, label %if.end54, !dbg !821

land.lhs.true:                                    ; preds = %lor.lhs.false, %if.end
  %16 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !822
  %rb_nodes13 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %16, i32 0, i32 0, !dbg !822
  %arrayidx14 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes13, i64 0, i64 0, !dbg !822
  %17 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx14, align 8, !dbg !822
  %cmp15 = icmp eq %struct.archive_rb_node* %17, null, !dbg !822
  br i1 %cmp15, label %land.lhs.true22, label %lor.lhs.false16, !dbg !822

lor.lhs.false16:                                  ; preds = %land.lhs.true
  %18 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !823
  %rb_nodes17 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %18, i32 0, i32 0, !dbg !823
  %arrayidx18 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes17, i64 0, i64 0, !dbg !823
  %19 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx18, align 8, !dbg !823
  %rb_info19 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %19, i32 0, i32 1, !dbg !823
  %20 = load i64, i64* %rb_info19, align 8, !dbg !823
  %and20 = and i64 %20, 1, !dbg !823
  %cmp21 = icmp eq i64 %and20, 0, !dbg !823
  br i1 %cmp21, label %land.lhs.true22, label %if.end54, !dbg !825

land.lhs.true22:                                  ; preds = %lor.lhs.false16, %land.lhs.true
  %21 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !826
  %rb_nodes23 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %21, i32 0, i32 0, !dbg !826
  %arrayidx24 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes23, i64 0, i64 1, !dbg !826
  %22 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx24, align 8, !dbg !826
  %cmp25 = icmp eq %struct.archive_rb_node* %22, null, !dbg !826
  br i1 %cmp25, label %if.then32, label %lor.lhs.false26, !dbg !826

lor.lhs.false26:                                  ; preds = %land.lhs.true22
  %23 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !827
  %rb_nodes27 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %23, i32 0, i32 0, !dbg !827
  %arrayidx28 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes27, i64 0, i64 1, !dbg !827
  %24 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx28, align 8, !dbg !827
  %rb_info29 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %24, i32 0, i32 1, !dbg !827
  %25 = load i64, i64* %rb_info29, align 8, !dbg !827
  %and30 = and i64 %25, 1, !dbg !827
  %cmp31 = icmp eq i64 %and30, 0, !dbg !827
  br i1 %cmp31, label %if.then32, label %if.end54, !dbg !828

if.then32:                                        ; preds = %lor.lhs.false26, %land.lhs.true22
  %26 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !830
  %cmp33 = icmp eq %struct.archive_rb_node* %26, null, !dbg !830
  br i1 %cmp33, label %if.else, label %land.lhs.true34, !dbg !830

land.lhs.true34:                                  ; preds = %if.then32
  %27 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !833
  %rb_info35 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %27, i32 0, i32 1, !dbg !833
  %28 = load i64, i64* %rb_info35, align 8, !dbg !833
  %and36 = and i64 %28, 1, !dbg !833
  %cmp37 = icmp ne i64 %and36, 0, !dbg !833
  br i1 %cmp37, label %if.then38, label %if.else, !dbg !833

if.then38:                                        ; preds = %land.lhs.true34
  %29 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !835
  %30 = load i32, i32* %other, align 4, !dbg !837
  call void @__archive_rb_tree_reparent_nodes(%struct.archive_rb_node* %29, i32 %30), !dbg !838
  %31 = load i32, i32* %other, align 4, !dbg !839
  %idxprom39 = zext i32 %31 to i64, !dbg !840
  %32 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !840
  %rb_nodes40 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %32, i32 0, i32 0, !dbg !841
  %arrayidx41 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes40, i64 0, i64 %idxprom39, !dbg !840
  %33 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx41, align 8, !dbg !840
  store %struct.archive_rb_node* %33, %struct.archive_rb_node** %brother, align 8, !dbg !842
  %34 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !843
  %cmp42 = icmp eq %struct.archive_rb_node* %34, null, !dbg !845
  br i1 %cmp42, label %if.then43, label %if.end44, !dbg !846

if.then43:                                        ; preds = %if.then38
  br label %while.end, !dbg !847

if.end44:                                         ; preds = %if.then38
  br label %if.end53, !dbg !848

if.else:                                          ; preds = %land.lhs.true34, %if.then32
  %35 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !849
  %rb_info45 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %35, i32 0, i32 1, !dbg !849
  %36 = load i64, i64* %rb_info45, align 8, !dbg !849
  %or = or i64 %36, 1, !dbg !849
  store i64 %or, i64* %rb_info45, align 8, !dbg !849
  %37 = load %struct.archive_rb_tree*, %struct.archive_rb_tree** %rbt.addr, align 8, !dbg !851
  %rbt_root = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %37, i32 0, i32 0, !dbg !851
  %38 = load %struct.archive_rb_node*, %struct.archive_rb_node** %rbt_root, align 8, !dbg !851
  %39 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !851
  %cmp46 = icmp eq %struct.archive_rb_node* %38, %39, !dbg !851
  br i1 %cmp46, label %if.then47, label %if.end48, !dbg !853

if.then47:                                        ; preds = %if.else
  br label %while.end, !dbg !854

if.end48:                                         ; preds = %if.else
  %40 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !855
  %rb_info49 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %40, i32 0, i32 1, !dbg !855
  %41 = load i64, i64* %rb_info49, align 8, !dbg !855
  %and50 = and i64 %41, 2, !dbg !855
  %tobool = icmp ne i64 %and50, 0, !dbg !855
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !855
  store i32 %cond, i32* %which.addr, align 4, !dbg !856
  %42 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !857
  %rb_info51 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %42, i32 0, i32 1, !dbg !857
  %43 = load i64, i64* %rb_info51, align 8, !dbg !857
  %and52 = and i64 %43, -4, !dbg !857
  %44 = inttoptr i64 %and52 to %struct.archive_rb_node*, !dbg !857
  store %struct.archive_rb_node* %44, %struct.archive_rb_node** %parent.addr, align 8, !dbg !858
  br label %while.cond, !dbg !859

if.end53:                                         ; preds = %if.end44
  br label %if.end54, !dbg !860

if.end54:                                         ; preds = %if.end53, %lor.lhs.false26, %lor.lhs.false16, %lor.lhs.false
  %45 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !861
  %cmp55 = icmp eq %struct.archive_rb_node* %45, null, !dbg !861
  br i1 %cmp55, label %if.else91, label %land.lhs.true56, !dbg !861

land.lhs.true56:                                  ; preds = %if.end54
  %46 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !863
  %rb_info57 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %46, i32 0, i32 1, !dbg !863
  %47 = load i64, i64* %rb_info57, align 8, !dbg !863
  %and58 = and i64 %47, 1, !dbg !863
  %cmp59 = icmp ne i64 %and58, 0, !dbg !863
  br i1 %cmp59, label %land.lhs.true60, label %if.else91, !dbg !865

land.lhs.true60:                                  ; preds = %land.lhs.true56
  %48 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !866
  %cmp61 = icmp eq %struct.archive_rb_node* %48, null, !dbg !866
  br i1 %cmp61, label %land.lhs.true66, label %lor.lhs.false62, !dbg !866

lor.lhs.false62:                                  ; preds = %land.lhs.true60
  %49 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !867
  %rb_info63 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %49, i32 0, i32 1, !dbg !867
  %50 = load i64, i64* %rb_info63, align 8, !dbg !867
  %and64 = and i64 %50, 1, !dbg !867
  %cmp65 = icmp eq i64 %and64, 0, !dbg !867
  br i1 %cmp65, label %land.lhs.true66, label %if.else91, !dbg !869

land.lhs.true66:                                  ; preds = %lor.lhs.false62, %land.lhs.true60
  %51 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !870
  %rb_nodes67 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %51, i32 0, i32 0, !dbg !870
  %arrayidx68 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes67, i64 0, i64 0, !dbg !870
  %52 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx68, align 8, !dbg !870
  %cmp69 = icmp eq %struct.archive_rb_node* %52, null, !dbg !870
  br i1 %cmp69, label %land.lhs.true76, label %lor.lhs.false70, !dbg !870

lor.lhs.false70:                                  ; preds = %land.lhs.true66
  %53 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !871
  %rb_nodes71 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %53, i32 0, i32 0, !dbg !871
  %arrayidx72 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes71, i64 0, i64 0, !dbg !871
  %54 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx72, align 8, !dbg !871
  %rb_info73 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %54, i32 0, i32 1, !dbg !871
  %55 = load i64, i64* %rb_info73, align 8, !dbg !871
  %and74 = and i64 %55, 1, !dbg !871
  %cmp75 = icmp eq i64 %and74, 0, !dbg !871
  br i1 %cmp75, label %land.lhs.true76, label %if.else91, !dbg !872

land.lhs.true76:                                  ; preds = %lor.lhs.false70, %land.lhs.true66
  %56 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !873
  %rb_nodes77 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %56, i32 0, i32 0, !dbg !873
  %arrayidx78 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes77, i64 0, i64 1, !dbg !873
  %57 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx78, align 8, !dbg !873
  %cmp79 = icmp eq %struct.archive_rb_node* %57, null, !dbg !873
  br i1 %cmp79, label %if.then86, label %lor.lhs.false80, !dbg !873

lor.lhs.false80:                                  ; preds = %land.lhs.true76
  %58 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !874
  %rb_nodes81 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %58, i32 0, i32 0, !dbg !874
  %arrayidx82 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes81, i64 0, i64 1, !dbg !874
  %59 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx82, align 8, !dbg !874
  %rb_info83 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %59, i32 0, i32 1, !dbg !874
  %60 = load i64, i64* %rb_info83, align 8, !dbg !874
  %and84 = and i64 %60, 1, !dbg !874
  %cmp85 = icmp eq i64 %and84, 0, !dbg !874
  br i1 %cmp85, label %if.then86, label %if.else91, !dbg !875

if.then86:                                        ; preds = %lor.lhs.false80, %land.lhs.true76
  %61 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !876
  %rb_info87 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %61, i32 0, i32 1, !dbg !876
  %62 = load i64, i64* %rb_info87, align 8, !dbg !876
  %and88 = and i64 %62, -2, !dbg !876
  store i64 %and88, i64* %rb_info87, align 8, !dbg !876
  %63 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !878
  %rb_info89 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %63, i32 0, i32 1, !dbg !878
  %64 = load i64, i64* %rb_info89, align 8, !dbg !878
  %or90 = or i64 %64, 1, !dbg !878
  store i64 %or90, i64* %rb_info89, align 8, !dbg !878
  br label %while.end, !dbg !879

if.else91:                                        ; preds = %lor.lhs.false80, %lor.lhs.false70, %lor.lhs.false62, %land.lhs.true56, %if.end54
  %65 = load i32, i32* %other, align 4, !dbg !880
  %idxprom92 = zext i32 %65 to i64, !dbg !880
  %66 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !880
  %rb_nodes93 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %66, i32 0, i32 0, !dbg !880
  %arrayidx94 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes93, i64 0, i64 %idxprom92, !dbg !880
  %67 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx94, align 8, !dbg !880
  %cmp95 = icmp eq %struct.archive_rb_node* %67, null, !dbg !880
  br i1 %cmp95, label %if.then103, label %lor.lhs.false96, !dbg !880

lor.lhs.false96:                                  ; preds = %if.else91
  %68 = load i32, i32* %other, align 4, !dbg !883
  %idxprom97 = zext i32 %68 to i64, !dbg !883
  %69 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !883
  %rb_nodes98 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %69, i32 0, i32 0, !dbg !883
  %arrayidx99 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes98, i64 0, i64 %idxprom97, !dbg !883
  %70 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx99, align 8, !dbg !883
  %rb_info100 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %70, i32 0, i32 1, !dbg !883
  %71 = load i64, i64* %rb_info100, align 8, !dbg !883
  %and101 = and i64 %71, 1, !dbg !883
  %cmp102 = icmp eq i64 %and101, 0, !dbg !883
  br i1 %cmp102, label %if.then103, label %if.end107, !dbg !883

if.then103:                                       ; preds = %lor.lhs.false96, %if.else91
  %72 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !885
  %73 = load i32, i32* %which.addr, align 4, !dbg !887
  call void @__archive_rb_tree_reparent_nodes(%struct.archive_rb_node* %72, i32 %73), !dbg !888
  %74 = load i32, i32* %other, align 4, !dbg !889
  %idxprom104 = zext i32 %74 to i64, !dbg !890
  %75 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !890
  %rb_nodes105 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %75, i32 0, i32 0, !dbg !891
  %arrayidx106 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes105, i64 0, i64 %idxprom104, !dbg !890
  %76 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx106, align 8, !dbg !890
  store %struct.archive_rb_node* %76, %struct.archive_rb_node** %brother, align 8, !dbg !892
  br label %if.end107, !dbg !893

if.end107:                                        ; preds = %if.then103, %lor.lhs.false96
  %77 = load i32, i32* %other, align 4, !dbg !894
  %idxprom108 = zext i32 %77 to i64, !dbg !896
  %78 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !896
  %rb_nodes109 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %78, i32 0, i32 0, !dbg !897
  %arrayidx110 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes109, i64 0, i64 %idxprom108, !dbg !896
  %79 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx110, align 8, !dbg !896
  %cmp111 = icmp eq %struct.archive_rb_node* %79, null, !dbg !898
  br i1 %cmp111, label %if.then112, label %if.end113, !dbg !899

if.then112:                                       ; preds = %if.end107
  br label %while.end, !dbg !900

if.end113:                                        ; preds = %if.end107
  %80 = load i32, i32* %other, align 4, !dbg !901
  %idxprom114 = zext i32 %80 to i64, !dbg !901
  %81 = load %struct.archive_rb_node*, %struct.archive_rb_node** %brother, align 8, !dbg !901
  %rb_nodes115 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %81, i32 0, i32 0, !dbg !901
  %arrayidx116 = getelementptr inbounds [2 x %struct.archive_rb_node*], [2 x %struct.archive_rb_node*]* %rb_nodes115, i64 0, i64 %idxprom114, !dbg !901
  %82 = load %struct.archive_rb_node*, %struct.archive_rb_node** %arrayidx116, align 8, !dbg !901
  %rb_info117 = getelementptr inbounds %struct.archive_rb_node, %struct.archive_rb_node* %82, i32 0, i32 1, !dbg !901
  %83 = load i64, i64* %rb_info117, align 8, !dbg !901
  %and118 = and i64 %83, -2, !dbg !901
  store i64 %and118, i64* %rb_info117, align 8, !dbg !901
  %84 = load %struct.archive_rb_node*, %struct.archive_rb_node** %parent.addr, align 8, !dbg !902
  %85 = load i32, i32* %other, align 4, !dbg !903
  call void @__archive_rb_tree_reparent_nodes(%struct.archive_rb_node* %84, i32 %85), !dbg !904
  br label %while.end, !dbg !905

while.end:                                        ; preds = %if.then, %if.then43, %if.then47, %if.then112, %if.end113, %if.then86, %lor.end
  ret void, !dbg !906
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!80, !81}
!llvm.ident = !{!82}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !19)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_rb.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !17, !5, !14, !18}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_node", file: !7, line: 34, size: 192, align: 64, elements: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_rb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !{!9, !13}
!9 = !DIDerivedType(tag: DW_TAG_member, name: "rb_nodes", scope: !6, file: !7, line: 35, baseType: !10, size: 128, align: 64)
!10 = !DICompositeType(tag: DW_TAG_array_type, baseType: !5, size: 128, align: 64, elements: !11)
!11 = !{!12}
!12 = !DISubrange(count: 2)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "rb_info", scope: !6, file: !7, line: 41, baseType: !14, size: 64, align: 64, offset: 128)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !15, line: 122, baseType: !16)
!15 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!16 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!18 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!19 = !{!20, !49, !52, !53, !54, !57, !60, !64, !65, !68, !71, !74, !77}
!20 = distinct !DISubprogram(name: "__archive_rb_tree_init", scope: !1, file: !1, line: 95, type: !21, isLocal: false, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{null, !23, !28}
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree", file: !7, line: 80, size: 128, align: 64, elements: !25)
!25 = !{!26, !27}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_root", scope: !24, file: !7, line: 81, baseType: !5, size: 64, align: 64)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_ops", scope: !24, file: !7, line: 82, baseType: !28, size: 64, align: 64, offset: 64)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !30)
!30 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree_ops", file: !7, line: 75, size: 128, align: 64, elements: !31)
!31 = !{!32, !41}
!32 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_nodes", scope: !30, file: !7, line: 76, baseType: !33, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_nodes_fn", file: !7, line: 70, baseType: !34)
!34 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !35)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !39, !39}
!38 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !6)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_key", scope: !30, file: !7, line: 77, baseType: !42, size: 64, align: 64, offset: 64)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_key_fn", file: !7, line: 72, baseType: !43)
!43 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !44)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DISubroutineType(types: !46)
!46 = !{!38, !39, !47}
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!49 = distinct !DISubprogram(name: "__archive_rb_tree_find_node", scope: !1, file: !1, line: 103, type: !50, isLocal: false, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!50 = !DISubroutineType(types: !51)
!51 = !{!5, !23, !47}
!52 = distinct !DISubprogram(name: "__archive_rb_tree_find_node_geq", scope: !1, file: !1, line: 119, type: !50, isLocal: false, isDefinition: true, scopeLine: 120, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!53 = distinct !DISubprogram(name: "__archive_rb_tree_find_node_leq", scope: !1, file: !1, line: 138, type: !50, isLocal: false, isDefinition: true, scopeLine: 139, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!54 = distinct !DISubprogram(name: "__archive_rb_tree_insert_node", scope: !1, file: !1, line: 157, type: !55, isLocal: false, isDefinition: true, scopeLine: 159, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!55 = !DISubroutineType(types: !56)
!56 = !{!38, !23, !5}
!57 = distinct !DISubprogram(name: "__archive_rb_tree_remove_node", scope: !1, file: !1, line: 492, type: !58, isLocal: false, isDefinition: true, scopeLine: 494, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!58 = !DISubroutineType(types: !59)
!59 = !{null, !23, !5}
!60 = distinct !DISubprogram(name: "__archive_rb_tree_iterate", scope: !1, file: !1, line: 675, type: !61, isLocal: false, isDefinition: true, scopeLine: 677, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!61 = !DISubroutineType(types: !62)
!62 = !{!5, !23, !5, !63}
!63 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !18)
!64 = distinct !DISubprogram(name: "__archive_rb_tree_insert_rebalance", scope: !1, file: !1, line: 273, type: !58, isLocal: true, isDefinition: true, scopeLine: 275, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!65 = distinct !DISubprogram(name: "__archive_rb_tree_reparent_nodes", scope: !1, file: !1, line: 231, type: !66, isLocal: true, isDefinition: true, scopeLine: 233, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!66 = !DISubroutineType(types: !67)
!67 = !{null, !5, !63}
!68 = distinct !DISubprogram(name: "__archive_rb_tree_prune_node", scope: !1, file: !1, line: 348, type: !69, isLocal: true, isDefinition: true, scopeLine: 350, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!69 = !DISubroutineType(types: !70)
!70 = !{null, !23, !5, !38}
!71 = distinct !DISubprogram(name: "__archive_rb_tree_removal_rebalance", scope: !1, file: !1, line: 549, type: !72, isLocal: true, isDefinition: true, scopeLine: 551, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!72 = !DISubroutineType(types: !73)
!73 = !{null, !23, !5, !18}
!74 = distinct !DISubprogram(name: "__archive_rb_tree_prune_blackred_branch", scope: !1, file: !1, line: 474, type: !75, isLocal: true, isDefinition: true, scopeLine: 476, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!75 = !DISubroutineType(types: !76)
!76 = !{null, !5, !18}
!77 = distinct !DISubprogram(name: "__archive_rb_tree_swap_prune_and_rebalance", scope: !1, file: !1, line: 371, type: !78, isLocal: true, isDefinition: true, scopeLine: 373, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!78 = !DISubroutineType(types: !79)
!79 = !{null, !23, !5, !5}
!80 = !{i32 2, !"Dwarf Version", i32 4}
!81 = !{i32 2, !"Debug Info Version", i32 3}
!82 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!83 = !DILocalVariable(name: "rbt", arg: 1, scope: !20, file: !1, line: 95, type: !23)
!84 = !DIExpression()
!85 = !DILocation(line: 95, column: 48, scope: !20)
!86 = !DILocalVariable(name: "ops", arg: 2, scope: !20, file: !1, line: 96, type: !28)
!87 = !DILocation(line: 96, column: 39, scope: !20)
!88 = !DILocation(line: 98, column: 17, scope: !20)
!89 = !DILocation(line: 98, column: 2, scope: !20)
!90 = !DILocation(line: 98, column: 7, scope: !20)
!91 = !DILocation(line: 98, column: 15, scope: !20)
!92 = !DILocation(line: 99, column: 32, scope: !20)
!93 = !DILocation(line: 99, column: 37, scope: !20)
!94 = !DILocation(line: 99, column: 47, scope: !20)
!95 = !DILocation(line: 100, column: 1, scope: !20)
!96 = !DILocalVariable(name: "rbt", arg: 1, scope: !49, file: !1, line: 103, type: !23)
!97 = !DILocation(line: 103, column: 53, scope: !49)
!98 = !DILocalVariable(name: "key", arg: 2, scope: !49, file: !1, line: 103, type: !47)
!99 = !DILocation(line: 103, column: 70, scope: !49)
!100 = !DILocalVariable(name: "compare_key", scope: !49, file: !1, line: 105, type: !42)
!101 = !DILocation(line: 105, column: 30, scope: !49)
!102 = !DILocation(line: 105, column: 44, scope: !49)
!103 = !DILocation(line: 105, column: 49, scope: !49)
!104 = !DILocation(line: 105, column: 58, scope: !49)
!105 = !DILocalVariable(name: "parent", scope: !49, file: !1, line: 106, type: !5)
!106 = !DILocation(line: 106, column: 26, scope: !49)
!107 = !DILocation(line: 106, column: 35, scope: !49)
!108 = !DILocation(line: 106, column: 40, scope: !49)
!109 = !DILocation(line: 108, column: 2, scope: !49)
!110 = !DILocation(line: 108, column: 10, scope: !111)
!111 = !DILexicalBlockFile(scope: !49, file: !1, discriminator: 1)
!112 = !DILocation(line: 108, column: 9, scope: !111)
!113 = !DILocation(line: 108, column: 2, scope: !111)
!114 = !DILocalVariable(name: "diff", scope: !115, file: !1, line: 109, type: !116)
!115 = distinct !DILexicalBlock(scope: !49, file: !1, line: 108, column: 33)
!116 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!117 = !DILocation(line: 109, column: 20, scope: !115)
!118 = !DILocation(line: 109, column: 29, scope: !115)
!119 = !DILocation(line: 109, column: 42, scope: !115)
!120 = !DILocation(line: 109, column: 50, scope: !115)
!121 = !DILocation(line: 109, column: 27, scope: !115)
!122 = !DILocation(line: 110, column: 7, scope: !123)
!123 = distinct !DILexicalBlock(scope: !115, file: !1, line: 110, column: 7)
!124 = !DILocation(line: 110, column: 12, scope: !123)
!125 = !DILocation(line: 110, column: 7, scope: !115)
!126 = !DILocation(line: 111, column: 11, scope: !123)
!127 = !DILocation(line: 111, column: 4, scope: !123)
!128 = !DILocation(line: 112, column: 29, scope: !115)
!129 = !DILocation(line: 112, column: 34, scope: !115)
!130 = !DILocation(line: 112, column: 12, scope: !115)
!131 = !DILocation(line: 112, column: 20, scope: !115)
!132 = !DILocation(line: 112, column: 10, scope: !115)
!133 = !DILocation(line: 108, column: 2, scope: !134)
!134 = !DILexicalBlockFile(scope: !49, file: !1, discriminator: 2)
!135 = !DILocation(line: 115, column: 2, scope: !49)
!136 = !DILocation(line: 116, column: 1, scope: !49)
!137 = !DILocalVariable(name: "rbt", arg: 1, scope: !52, file: !1, line: 119, type: !23)
!138 = !DILocation(line: 119, column: 57, scope: !52)
!139 = !DILocalVariable(name: "key", arg: 2, scope: !52, file: !1, line: 119, type: !47)
!140 = !DILocation(line: 119, column: 74, scope: !52)
!141 = !DILocalVariable(name: "compare_key", scope: !52, file: !1, line: 121, type: !42)
!142 = !DILocation(line: 121, column: 30, scope: !52)
!143 = !DILocation(line: 121, column: 44, scope: !52)
!144 = !DILocation(line: 121, column: 49, scope: !52)
!145 = !DILocation(line: 121, column: 58, scope: !52)
!146 = !DILocalVariable(name: "parent", scope: !52, file: !1, line: 122, type: !5)
!147 = !DILocation(line: 122, column: 26, scope: !52)
!148 = !DILocation(line: 122, column: 35, scope: !52)
!149 = !DILocation(line: 122, column: 40, scope: !52)
!150 = !DILocalVariable(name: "last", scope: !52, file: !1, line: 123, type: !5)
!151 = !DILocation(line: 123, column: 26, scope: !52)
!152 = !DILocation(line: 125, column: 2, scope: !52)
!153 = !DILocation(line: 125, column: 10, scope: !154)
!154 = !DILexicalBlockFile(scope: !52, file: !1, discriminator: 1)
!155 = !DILocation(line: 125, column: 9, scope: !154)
!156 = !DILocation(line: 125, column: 2, scope: !154)
!157 = !DILocalVariable(name: "diff", scope: !158, file: !1, line: 126, type: !116)
!158 = distinct !DILexicalBlock(scope: !52, file: !1, line: 125, column: 33)
!159 = !DILocation(line: 126, column: 20, scope: !158)
!160 = !DILocation(line: 126, column: 29, scope: !158)
!161 = !DILocation(line: 126, column: 42, scope: !158)
!162 = !DILocation(line: 126, column: 50, scope: !158)
!163 = !DILocation(line: 126, column: 27, scope: !158)
!164 = !DILocation(line: 127, column: 7, scope: !165)
!165 = distinct !DILexicalBlock(scope: !158, file: !1, line: 127, column: 7)
!166 = !DILocation(line: 127, column: 12, scope: !165)
!167 = !DILocation(line: 127, column: 7, scope: !158)
!168 = !DILocation(line: 128, column: 11, scope: !165)
!169 = !DILocation(line: 128, column: 4, scope: !165)
!170 = !DILocation(line: 129, column: 7, scope: !171)
!171 = distinct !DILexicalBlock(scope: !158, file: !1, line: 129, column: 7)
!172 = !DILocation(line: 129, column: 12, scope: !171)
!173 = !DILocation(line: 129, column: 7, scope: !158)
!174 = !DILocation(line: 130, column: 11, scope: !171)
!175 = !DILocation(line: 130, column: 9, scope: !171)
!176 = !DILocation(line: 130, column: 4, scope: !171)
!177 = !DILocation(line: 131, column: 29, scope: !158)
!178 = !DILocation(line: 131, column: 34, scope: !158)
!179 = !DILocation(line: 131, column: 12, scope: !158)
!180 = !DILocation(line: 131, column: 20, scope: !158)
!181 = !DILocation(line: 131, column: 10, scope: !158)
!182 = !DILocation(line: 125, column: 2, scope: !183)
!183 = !DILexicalBlockFile(scope: !52, file: !1, discriminator: 2)
!184 = !DILocation(line: 134, column: 9, scope: !52)
!185 = !DILocation(line: 134, column: 2, scope: !52)
!186 = !DILocation(line: 135, column: 1, scope: !52)
!187 = !DILocalVariable(name: "rbt", arg: 1, scope: !53, file: !1, line: 138, type: !23)
!188 = !DILocation(line: 138, column: 57, scope: !53)
!189 = !DILocalVariable(name: "key", arg: 2, scope: !53, file: !1, line: 138, type: !47)
!190 = !DILocation(line: 138, column: 74, scope: !53)
!191 = !DILocalVariable(name: "compare_key", scope: !53, file: !1, line: 140, type: !42)
!192 = !DILocation(line: 140, column: 30, scope: !53)
!193 = !DILocation(line: 140, column: 44, scope: !53)
!194 = !DILocation(line: 140, column: 49, scope: !53)
!195 = !DILocation(line: 140, column: 58, scope: !53)
!196 = !DILocalVariable(name: "parent", scope: !53, file: !1, line: 141, type: !5)
!197 = !DILocation(line: 141, column: 26, scope: !53)
!198 = !DILocation(line: 141, column: 35, scope: !53)
!199 = !DILocation(line: 141, column: 40, scope: !53)
!200 = !DILocalVariable(name: "last", scope: !53, file: !1, line: 142, type: !5)
!201 = !DILocation(line: 142, column: 26, scope: !53)
!202 = !DILocation(line: 144, column: 2, scope: !53)
!203 = !DILocation(line: 144, column: 10, scope: !204)
!204 = !DILexicalBlockFile(scope: !53, file: !1, discriminator: 1)
!205 = !DILocation(line: 144, column: 9, scope: !204)
!206 = !DILocation(line: 144, column: 2, scope: !204)
!207 = !DILocalVariable(name: "diff", scope: !208, file: !1, line: 145, type: !116)
!208 = distinct !DILexicalBlock(scope: !53, file: !1, line: 144, column: 33)
!209 = !DILocation(line: 145, column: 20, scope: !208)
!210 = !DILocation(line: 145, column: 29, scope: !208)
!211 = !DILocation(line: 145, column: 42, scope: !208)
!212 = !DILocation(line: 145, column: 50, scope: !208)
!213 = !DILocation(line: 145, column: 27, scope: !208)
!214 = !DILocation(line: 146, column: 7, scope: !215)
!215 = distinct !DILexicalBlock(scope: !208, file: !1, line: 146, column: 7)
!216 = !DILocation(line: 146, column: 12, scope: !215)
!217 = !DILocation(line: 146, column: 7, scope: !208)
!218 = !DILocation(line: 147, column: 11, scope: !215)
!219 = !DILocation(line: 147, column: 4, scope: !215)
!220 = !DILocation(line: 148, column: 7, scope: !221)
!221 = distinct !DILexicalBlock(scope: !208, file: !1, line: 148, column: 7)
!222 = !DILocation(line: 148, column: 12, scope: !221)
!223 = !DILocation(line: 148, column: 7, scope: !208)
!224 = !DILocation(line: 149, column: 11, scope: !221)
!225 = !DILocation(line: 149, column: 9, scope: !221)
!226 = !DILocation(line: 149, column: 4, scope: !221)
!227 = !DILocation(line: 150, column: 29, scope: !208)
!228 = !DILocation(line: 150, column: 34, scope: !208)
!229 = !DILocation(line: 150, column: 12, scope: !208)
!230 = !DILocation(line: 150, column: 20, scope: !208)
!231 = !DILocation(line: 150, column: 10, scope: !208)
!232 = !DILocation(line: 144, column: 2, scope: !233)
!233 = !DILexicalBlockFile(scope: !53, file: !1, discriminator: 2)
!234 = !DILocation(line: 153, column: 9, scope: !53)
!235 = !DILocation(line: 153, column: 2, scope: !53)
!236 = !DILocation(line: 154, column: 1, scope: !53)
!237 = !DILocalVariable(name: "rbt", arg: 1, scope: !54, file: !1, line: 157, type: !23)
!238 = !DILocation(line: 157, column: 55, scope: !54)
!239 = !DILocalVariable(name: "self", arg: 2, scope: !54, file: !1, line: 158, type: !5)
!240 = !DILocation(line: 158, column: 29, scope: !54)
!241 = !DILocalVariable(name: "compare_nodes", scope: !54, file: !1, line: 160, type: !33)
!242 = !DILocation(line: 160, column: 32, scope: !54)
!243 = !DILocation(line: 160, column: 48, scope: !54)
!244 = !DILocation(line: 160, column: 53, scope: !54)
!245 = !DILocation(line: 160, column: 62, scope: !54)
!246 = !DILocalVariable(name: "parent", scope: !54, file: !1, line: 161, type: !5)
!247 = !DILocation(line: 161, column: 26, scope: !54)
!248 = !DILocalVariable(name: "tmp", scope: !54, file: !1, line: 161, type: !5)
!249 = !DILocation(line: 161, column: 35, scope: !54)
!250 = !DILocalVariable(name: "position", scope: !54, file: !1, line: 162, type: !18)
!251 = !DILocation(line: 162, column: 15, scope: !54)
!252 = !DILocalVariable(name: "rebalance", scope: !54, file: !1, line: 163, type: !38)
!253 = !DILocation(line: 163, column: 6, scope: !54)
!254 = !DILocation(line: 165, column: 8, scope: !54)
!255 = !DILocation(line: 165, column: 13, scope: !54)
!256 = !DILocation(line: 165, column: 6, scope: !54)
!257 = !DILocation(line: 174, column: 46, scope: !54)
!258 = !DILocation(line: 174, column: 51, scope: !54)
!259 = !DILocation(line: 174, column: 37, scope: !54)
!260 = !DILocation(line: 174, column: 11, scope: !54)
!261 = !DILocation(line: 174, column: 9, scope: !54)
!262 = !DILocation(line: 175, column: 11, scope: !54)
!263 = !DILocation(line: 180, column: 2, scope: !54)
!264 = !DILocation(line: 180, column: 10, scope: !265)
!265 = !DILexicalBlockFile(scope: !54, file: !1, discriminator: 1)
!266 = !DILocation(line: 180, column: 9, scope: !265)
!267 = !DILocation(line: 180, column: 2, scope: !265)
!268 = !DILocalVariable(name: "diff", scope: !269, file: !1, line: 181, type: !116)
!269 = distinct !DILexicalBlock(scope: !54, file: !1, line: 180, column: 30)
!270 = !DILocation(line: 181, column: 20, scope: !269)
!271 = !DILocation(line: 181, column: 29, scope: !269)
!272 = !DILocation(line: 181, column: 44, scope: !269)
!273 = !DILocation(line: 181, column: 49, scope: !269)
!274 = !DILocation(line: 181, column: 27, scope: !269)
!275 = !DILocation(line: 182, column: 7, scope: !276)
!276 = distinct !DILexicalBlock(scope: !269, file: !1, line: 182, column: 7)
!277 = !DILocation(line: 182, column: 12, scope: !276)
!278 = !DILocation(line: 182, column: 7, scope: !269)
!279 = !DILocation(line: 186, column: 4, scope: !280)
!280 = distinct !DILexicalBlock(scope: !276, file: !1, line: 182, column: 18)
!281 = !DILocation(line: 188, column: 12, scope: !269)
!282 = !DILocation(line: 188, column: 10, scope: !269)
!283 = !DILocation(line: 189, column: 15, scope: !269)
!284 = !DILocation(line: 189, column: 20, scope: !269)
!285 = !DILocation(line: 189, column: 12, scope: !269)
!286 = !DILocation(line: 190, column: 26, scope: !269)
!287 = !DILocation(line: 190, column: 9, scope: !269)
!288 = !DILocation(line: 190, column: 17, scope: !269)
!289 = !DILocation(line: 190, column: 7, scope: !269)
!290 = !DILocation(line: 180, column: 2, scope: !291)
!291 = !DILexicalBlockFile(scope: !54, file: !1, discriminator: 2)
!292 = !DILocation(line: 196, column: 2, scope: !54)
!293 = !DILocation(line: 197, column: 2, scope: !54)
!294 = !DILocation(line: 197, column: 2, scope: !265)
!295 = !DILocation(line: 197, column: 2, scope: !291)
!296 = !DILocation(line: 197, column: 2, scope: !297)
!297 = !DILexicalBlockFile(scope: !54, file: !1, discriminator: 3)
!298 = !DILocation(line: 198, column: 6, scope: !299)
!299 = distinct !DILexicalBlock(scope: !54, file: !1, line: 198, column: 6)
!300 = !DILocation(line: 198, column: 51, scope: !299)
!301 = !DILocation(line: 198, column: 56, scope: !299)
!302 = !DILocation(line: 198, column: 42, scope: !299)
!303 = !DILocation(line: 198, column: 16, scope: !299)
!304 = !DILocation(line: 198, column: 13, scope: !299)
!305 = !DILocation(line: 198, column: 6, scope: !54)
!306 = !DILocation(line: 199, column: 3, scope: !307)
!307 = distinct !DILexicalBlock(scope: !299, file: !1, line: 198, column: 66)
!308 = !DILocation(line: 200, column: 13, scope: !307)
!309 = !DILocation(line: 201, column: 2, scope: !307)
!310 = !DILocation(line: 206, column: 3, scope: !311)
!311 = distinct !DILexicalBlock(scope: !299, file: !1, line: 201, column: 9)
!312 = !DILocation(line: 207, column: 15, scope: !311)
!313 = !DILocation(line: 207, column: 15, scope: !314)
!314 = !DILexicalBlockFile(scope: !311, file: !1, discriminator: 1)
!315 = !DILocation(line: 207, column: 15, scope: !316)
!316 = !DILexicalBlockFile(scope: !311, file: !1, discriminator: 2)
!317 = !DILocation(line: 207, column: 13, scope: !316)
!318 = !DILocation(line: 209, column: 35, scope: !54)
!319 = !DILocation(line: 209, column: 18, scope: !54)
!320 = !DILocation(line: 209, column: 26, scope: !54)
!321 = !DILocation(line: 209, column: 2, scope: !54)
!322 = !DILocation(line: 209, column: 8, scope: !54)
!323 = !DILocation(line: 209, column: 16, scope: !54)
!324 = !DILocation(line: 210, column: 36, scope: !54)
!325 = !DILocation(line: 210, column: 19, scope: !54)
!326 = !DILocation(line: 210, column: 27, scope: !54)
!327 = !DILocation(line: 210, column: 2, scope: !54)
!328 = !DILocation(line: 210, column: 8, scope: !54)
!329 = !DILocation(line: 210, column: 17, scope: !54)
!330 = !DILocation(line: 211, column: 31, scope: !54)
!331 = !DILocation(line: 211, column: 19, scope: !54)
!332 = !DILocation(line: 211, column: 2, scope: !54)
!333 = !DILocation(line: 211, column: 10, scope: !54)
!334 = !DILocation(line: 211, column: 29, scope: !54)
!335 = !DILocation(line: 216, column: 6, scope: !336)
!336 = distinct !DILexicalBlock(scope: !54, file: !1, line: 216, column: 6)
!337 = !DILocation(line: 216, column: 6, scope: !54)
!338 = !DILocation(line: 217, column: 38, scope: !336)
!339 = !DILocation(line: 217, column: 43, scope: !336)
!340 = !DILocation(line: 217, column: 3, scope: !336)
!341 = !DILocation(line: 219, column: 2, scope: !54)
!342 = !DILocation(line: 220, column: 1, scope: !54)
!343 = !DILocalVariable(name: "rbt", arg: 1, scope: !64, file: !1, line: 273, type: !23)
!344 = !DILocation(line: 273, column: 60, scope: !64)
!345 = !DILocalVariable(name: "self", arg: 2, scope: !64, file: !1, line: 274, type: !5)
!346 = !DILocation(line: 274, column: 29, scope: !64)
!347 = !DILocalVariable(name: "father", scope: !64, file: !1, line: 276, type: !5)
!348 = !DILocation(line: 276, column: 27, scope: !64)
!349 = !DILocation(line: 276, column: 36, scope: !64)
!350 = !DILocalVariable(name: "grandpa", scope: !64, file: !1, line: 277, type: !5)
!351 = !DILocation(line: 277, column: 27, scope: !64)
!352 = !DILocalVariable(name: "uncle", scope: !64, file: !1, line: 278, type: !5)
!353 = !DILocation(line: 278, column: 27, scope: !64)
!354 = !DILocalVariable(name: "which", scope: !64, file: !1, line: 279, type: !18)
!355 = !DILocation(line: 279, column: 15, scope: !64)
!356 = !DILocalVariable(name: "other", scope: !64, file: !1, line: 280, type: !18)
!357 = !DILocation(line: 280, column: 15, scope: !64)
!358 = !DILocation(line: 282, column: 2, scope: !64)
!359 = !DILocation(line: 287, column: 13, scope: !360)
!360 = distinct !DILexicalBlock(scope: !361, file: !1, line: 282, column: 11)
!361 = distinct !DILexicalBlock(scope: !362, file: !1, line: 282, column: 2)
!362 = distinct !DILexicalBlock(scope: !64, file: !1, line: 282, column: 2)
!363 = !DILocation(line: 287, column: 11, scope: !360)
!364 = !DILocation(line: 288, column: 12, scope: !360)
!365 = !DILocation(line: 288, column: 22, scope: !360)
!366 = !DILocation(line: 288, column: 31, scope: !360)
!367 = !DILocation(line: 288, column: 19, scope: !360)
!368 = !DILocation(line: 288, column: 9, scope: !360)
!369 = !DILocation(line: 289, column: 11, scope: !360)
!370 = !DILocation(line: 289, column: 17, scope: !360)
!371 = !DILocation(line: 289, column: 9, scope: !360)
!372 = !DILocation(line: 290, column: 29, scope: !360)
!373 = !DILocation(line: 290, column: 11, scope: !360)
!374 = !DILocation(line: 290, column: 20, scope: !360)
!375 = !DILocation(line: 290, column: 9, scope: !360)
!376 = !DILocation(line: 292, column: 7, scope: !377)
!377 = distinct !DILexicalBlock(scope: !360, file: !1, line: 292, column: 7)
!378 = !DILocation(line: 292, column: 7, scope: !379)
!379 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 1)
!380 = !DILocation(line: 293, column: 4, scope: !377)
!381 = !DILocation(line: 301, column: 3, scope: !360)
!382 = !DILocation(line: 302, column: 3, scope: !360)
!383 = !DILocation(line: 303, column: 7, scope: !384)
!384 = distinct !DILexicalBlock(scope: !360, file: !1, line: 303, column: 7)
!385 = !DILocation(line: 303, column: 7, scope: !360)
!386 = !DILocation(line: 308, column: 4, scope: !387)
!387 = distinct !DILexicalBlock(scope: !384, file: !1, line: 303, column: 32)
!388 = !DILocation(line: 310, column: 3, scope: !360)
!389 = !DILocation(line: 311, column: 10, scope: !360)
!390 = !DILocation(line: 311, column: 8, scope: !360)
!391 = !DILocation(line: 312, column: 12, scope: !360)
!392 = !DILocation(line: 312, column: 10, scope: !360)
!393 = !DILocation(line: 313, column: 7, scope: !394)
!394 = distinct !DILexicalBlock(scope: !360, file: !1, line: 313, column: 7)
!395 = !DILocation(line: 313, column: 7, scope: !396)
!396 = !DILexicalBlockFile(scope: !394, file: !1, discriminator: 1)
!397 = !DILocation(line: 317, column: 4, scope: !398)
!398 = distinct !DILexicalBlock(scope: !394, file: !1, line: 313, column: 27)
!399 = !DILocation(line: 282, column: 2, scope: !400)
!400 = !DILexicalBlockFile(scope: !361, file: !1, discriminator: 1)
!401 = !DILocation(line: 324, column: 6, scope: !402)
!402 = distinct !DILexicalBlock(scope: !64, file: !1, line: 324, column: 6)
!403 = !DILocation(line: 324, column: 31, scope: !402)
!404 = !DILocation(line: 324, column: 14, scope: !402)
!405 = !DILocation(line: 324, column: 22, scope: !402)
!406 = !DILocation(line: 324, column: 11, scope: !402)
!407 = !DILocation(line: 324, column: 6, scope: !64)
!408 = !DILocation(line: 331, column: 36, scope: !409)
!409 = distinct !DILexicalBlock(scope: !402, file: !1, line: 324, column: 39)
!410 = !DILocation(line: 331, column: 44, scope: !409)
!411 = !DILocation(line: 331, column: 3, scope: !409)
!412 = !DILocation(line: 332, column: 2, scope: !409)
!413 = !DILocation(line: 339, column: 35, scope: !64)
!414 = !DILocation(line: 339, column: 44, scope: !64)
!415 = !DILocation(line: 339, column: 2, scope: !64)
!416 = !DILocation(line: 344, column: 2, scope: !64)
!417 = !DILocation(line: 345, column: 1, scope: !64)
!418 = !DILocation(line: 345, column: 1, scope: !419)
!419 = !DILexicalBlockFile(scope: !64, file: !1, discriminator: 1)
!420 = !DILocalVariable(name: "rbt", arg: 1, scope: !57, file: !1, line: 492, type: !23)
!421 = !DILocation(line: 492, column: 55, scope: !57)
!422 = !DILocalVariable(name: "self", arg: 2, scope: !57, file: !1, line: 493, type: !5)
!423 = !DILocation(line: 493, column: 29, scope: !57)
!424 = !DILocalVariable(name: "standin", scope: !57, file: !1, line: 495, type: !5)
!425 = !DILocation(line: 495, column: 26, scope: !57)
!426 = !DILocalVariable(name: "which", scope: !57, file: !1, line: 496, type: !18)
!427 = !DILocation(line: 496, column: 15, scope: !57)
!428 = !DILocation(line: 515, column: 6, scope: !429)
!429 = distinct !DILexicalBlock(scope: !57, file: !1, line: 515, column: 6)
!430 = !DILocation(line: 515, column: 6, scope: !431)
!431 = !DILexicalBlockFile(scope: !429, file: !1, discriminator: 1)
!432 = !DILocation(line: 515, column: 6, scope: !433)
!433 = !DILexicalBlockFile(scope: !429, file: !1, discriminator: 2)
!434 = !DILocalVariable(name: "rebalance", scope: !435, file: !1, line: 516, type: !116)
!435 = distinct !DILexicalBlock(scope: !429, file: !1, line: 515, column: 28)
!436 = !DILocation(line: 516, column: 13, scope: !435)
!437 = !DILocation(line: 516, column: 25, scope: !435)
!438 = !DILocation(line: 516, column: 25, scope: !439)
!439 = !DILexicalBlockFile(scope: !435, file: !1, discriminator: 1)
!440 = !DILocation(line: 516, column: 42, scope: !439)
!441 = !DILocation(line: 516, column: 46, scope: !442)
!442 = !DILexicalBlockFile(scope: !435, file: !1, discriminator: 2)
!443 = !DILocation(line: 516, column: 45, scope: !442)
!444 = !DILocation(line: 516, column: 42, scope: !445)
!445 = !DILexicalBlockFile(scope: !435, file: !1, discriminator: 3)
!446 = !DILocation(line: 516, column: 13, scope: !445)
!447 = !DILocation(line: 517, column: 32, scope: !435)
!448 = !DILocation(line: 517, column: 37, scope: !435)
!449 = !DILocation(line: 517, column: 43, scope: !435)
!450 = !DILocation(line: 517, column: 3, scope: !435)
!451 = !DILocation(line: 518, column: 3, scope: !435)
!452 = !DILocation(line: 520, column: 7, scope: !453)
!453 = distinct !DILexicalBlock(scope: !57, file: !1, line: 520, column: 6)
!454 = !DILocation(line: 520, column: 7, scope: !455)
!455 = !DILexicalBlockFile(scope: !453, file: !1, discriminator: 1)
!456 = !DILocation(line: 520, column: 7, scope: !457)
!457 = !DILexicalBlockFile(scope: !453, file: !1, discriminator: 2)
!458 = !DILocation(line: 520, column: 6, scope: !457)
!459 = !DILocation(line: 529, column: 11, scope: !460)
!460 = distinct !DILexicalBlock(scope: !453, file: !1, line: 520, column: 31)
!461 = !DILocation(line: 529, column: 9, scope: !460)
!462 = !DILocation(line: 530, column: 43, scope: !460)
!463 = !DILocation(line: 530, column: 49, scope: !460)
!464 = !DILocation(line: 530, column: 3, scope: !460)
!465 = !DILocation(line: 531, column: 3, scope: !460)
!466 = !DILocation(line: 538, column: 10, scope: !57)
!467 = !DILocation(line: 538, column: 28, scope: !57)
!468 = !DILocation(line: 538, column: 8, scope: !57)
!469 = !DILocation(line: 544, column: 38, scope: !57)
!470 = !DILocation(line: 544, column: 43, scope: !57)
!471 = !DILocation(line: 544, column: 49, scope: !57)
!472 = !DILocation(line: 544, column: 12, scope: !57)
!473 = !DILocation(line: 544, column: 10, scope: !57)
!474 = !DILocation(line: 545, column: 45, scope: !57)
!475 = !DILocation(line: 545, column: 50, scope: !57)
!476 = !DILocation(line: 545, column: 56, scope: !57)
!477 = !DILocation(line: 545, column: 2, scope: !57)
!478 = !DILocation(line: 546, column: 1, scope: !57)
!479 = !DILocation(line: 546, column: 1, scope: !480)
!480 = !DILexicalBlockFile(scope: !57, file: !1, discriminator: 1)
!481 = !DILocalVariable(name: "rbt", arg: 1, scope: !68, file: !1, line: 348, type: !23)
!482 = !DILocation(line: 348, column: 54, scope: !68)
!483 = !DILocalVariable(name: "self", arg: 2, scope: !68, file: !1, line: 349, type: !5)
!484 = !DILocation(line: 349, column: 29, scope: !68)
!485 = !DILocalVariable(name: "rebalance", arg: 3, scope: !68, file: !1, line: 349, type: !38)
!486 = !DILocation(line: 349, column: 39, scope: !68)
!487 = !DILocalVariable(name: "which", scope: !68, file: !1, line: 351, type: !63)
!488 = !DILocation(line: 351, column: 21, scope: !68)
!489 = !DILocation(line: 351, column: 29, scope: !68)
!490 = !DILocalVariable(name: "father", scope: !68, file: !1, line: 352, type: !5)
!491 = !DILocation(line: 352, column: 26, scope: !68)
!492 = !DILocation(line: 352, column: 35, scope: !68)
!493 = !DILocation(line: 358, column: 28, scope: !68)
!494 = !DILocation(line: 358, column: 34, scope: !68)
!495 = !DILocation(line: 358, column: 19, scope: !68)
!496 = !DILocation(line: 358, column: 2, scope: !68)
!497 = !DILocation(line: 358, column: 10, scope: !68)
!498 = !DILocation(line: 358, column: 26, scope: !68)
!499 = !DILocation(line: 363, column: 6, scope: !500)
!500 = distinct !DILexicalBlock(scope: !68, file: !1, line: 363, column: 6)
!501 = !DILocation(line: 363, column: 6, scope: !68)
!502 = !DILocation(line: 364, column: 39, scope: !500)
!503 = !DILocation(line: 364, column: 44, scope: !500)
!504 = !DILocation(line: 364, column: 52, scope: !500)
!505 = !DILocation(line: 364, column: 3, scope: !500)
!506 = !DILocation(line: 365, column: 1, scope: !68)
!507 = !DILocalVariable(name: "self", arg: 1, scope: !74, file: !1, line: 475, type: !5)
!508 = !DILocation(line: 475, column: 29, scope: !74)
!509 = !DILocalVariable(name: "which", arg: 2, scope: !74, file: !1, line: 475, type: !18)
!510 = !DILocation(line: 475, column: 48, scope: !74)
!511 = !DILocalVariable(name: "father", scope: !74, file: !1, line: 477, type: !5)
!512 = !DILocation(line: 477, column: 26, scope: !74)
!513 = !DILocation(line: 477, column: 35, scope: !74)
!514 = !DILocalVariable(name: "son", scope: !74, file: !1, line: 478, type: !5)
!515 = !DILocation(line: 478, column: 26, scope: !74)
!516 = !DILocation(line: 478, column: 47, scope: !74)
!517 = !DILocation(line: 478, column: 32, scope: !74)
!518 = !DILocation(line: 478, column: 38, scope: !74)
!519 = !DILocation(line: 484, column: 2, scope: !74)
!520 = !DILocation(line: 485, column: 39, scope: !74)
!521 = !DILocation(line: 485, column: 19, scope: !74)
!522 = !DILocation(line: 485, column: 2, scope: !74)
!523 = !DILocation(line: 485, column: 10, scope: !74)
!524 = !DILocation(line: 485, column: 37, scope: !74)
!525 = !DILocation(line: 486, column: 2, scope: !74)
!526 = !DILocation(line: 487, column: 1, scope: !74)
!527 = !DILocalVariable(name: "rbt", arg: 1, scope: !60, file: !1, line: 675, type: !23)
!528 = !DILocation(line: 675, column: 51, scope: !60)
!529 = !DILocalVariable(name: "self", arg: 2, scope: !60, file: !1, line: 676, type: !5)
!530 = !DILocation(line: 676, column: 29, scope: !60)
!531 = !DILocalVariable(name: "direction", arg: 3, scope: !60, file: !1, line: 676, type: !63)
!532 = !DILocation(line: 676, column: 54, scope: !60)
!533 = !DILocalVariable(name: "other", scope: !60, file: !1, line: 678, type: !63)
!534 = !DILocation(line: 678, column: 21, scope: !60)
!535 = !DILocation(line: 678, column: 29, scope: !60)
!536 = !DILocation(line: 678, column: 39, scope: !60)
!537 = !DILocation(line: 680, column: 6, scope: !538)
!538 = distinct !DILexicalBlock(scope: !60, file: !1, line: 680, column: 6)
!539 = !DILocation(line: 680, column: 11, scope: !538)
!540 = !DILocation(line: 680, column: 6, scope: !60)
!541 = !DILocation(line: 681, column: 10, scope: !542)
!542 = distinct !DILexicalBlock(scope: !538, file: !1, line: 680, column: 20)
!543 = !DILocation(line: 681, column: 15, scope: !542)
!544 = !DILocation(line: 681, column: 8, scope: !542)
!545 = !DILocation(line: 682, column: 7, scope: !546)
!546 = distinct !DILexicalBlock(scope: !542, file: !1, line: 682, column: 7)
!547 = !DILocation(line: 682, column: 7, scope: !542)
!548 = !DILocation(line: 683, column: 4, scope: !546)
!549 = !DILocation(line: 684, column: 3, scope: !542)
!550 = !DILocation(line: 684, column: 11, scope: !551)
!551 = !DILexicalBlockFile(scope: !542, file: !1, discriminator: 1)
!552 = !DILocation(line: 684, column: 10, scope: !551)
!553 = !DILocation(line: 684, column: 3, scope: !551)
!554 = !DILocation(line: 685, column: 26, scope: !542)
!555 = !DILocation(line: 685, column: 11, scope: !542)
!556 = !DILocation(line: 685, column: 17, scope: !542)
!557 = !DILocation(line: 685, column: 9, scope: !542)
!558 = !DILocation(line: 684, column: 3, scope: !559)
!559 = !DILexicalBlockFile(scope: !542, file: !1, discriminator: 2)
!560 = !DILocation(line: 686, column: 10, scope: !542)
!561 = !DILocation(line: 686, column: 3, scope: !542)
!562 = !DILocation(line: 692, column: 6, scope: !563)
!563 = distinct !DILexicalBlock(scope: !60, file: !1, line: 692, column: 6)
!564 = !DILocation(line: 692, column: 6, scope: !60)
!565 = !DILocation(line: 693, column: 3, scope: !566)
!566 = distinct !DILexicalBlock(scope: !563, file: !1, line: 692, column: 48)
!567 = !DILocation(line: 693, column: 11, scope: !568)
!568 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 1)
!569 = !DILocation(line: 693, column: 10, scope: !568)
!570 = !DILocation(line: 693, column: 3, scope: !568)
!571 = !DILocation(line: 694, column: 8, scope: !572)
!572 = distinct !DILexicalBlock(scope: !573, file: !1, line: 694, column: 8)
!573 = distinct !DILexicalBlock(scope: !566, file: !1, line: 693, column: 33)
!574 = !DILocation(line: 694, column: 31, scope: !572)
!575 = !DILocation(line: 694, column: 14, scope: !572)
!576 = !DILocation(line: 694, column: 8, scope: !573)
!577 = !DILocation(line: 695, column: 12, scope: !572)
!578 = !DILocation(line: 695, column: 5, scope: !572)
!579 = !DILocation(line: 696, column: 11, scope: !573)
!580 = !DILocation(line: 696, column: 9, scope: !573)
!581 = !DILocation(line: 693, column: 3, scope: !582)
!582 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 2)
!583 = !DILocation(line: 698, column: 3, scope: !566)
!584 = !DILocation(line: 705, column: 24, scope: !60)
!585 = !DILocation(line: 705, column: 9, scope: !60)
!586 = !DILocation(line: 705, column: 15, scope: !60)
!587 = !DILocation(line: 705, column: 7, scope: !60)
!588 = !DILocation(line: 706, column: 2, scope: !60)
!589 = !DILocation(line: 706, column: 10, scope: !590)
!590 = !DILexicalBlockFile(scope: !60, file: !1, discriminator: 1)
!591 = !DILocation(line: 706, column: 9, scope: !590)
!592 = !DILocation(line: 706, column: 2, scope: !590)
!593 = !DILocation(line: 707, column: 25, scope: !60)
!594 = !DILocation(line: 707, column: 10, scope: !60)
!595 = !DILocation(line: 707, column: 16, scope: !60)
!596 = !DILocation(line: 707, column: 8, scope: !60)
!597 = !DILocation(line: 706, column: 2, scope: !598)
!598 = !DILexicalBlockFile(scope: !60, file: !1, discriminator: 2)
!599 = !DILocation(line: 708, column: 9, scope: !60)
!600 = !DILocation(line: 708, column: 2, scope: !60)
!601 = !DILocation(line: 709, column: 1, scope: !60)
!602 = !DILocalVariable(name: "rbt", arg: 1, scope: !77, file: !1, line: 371, type: !23)
!603 = !DILocation(line: 371, column: 68, scope: !77)
!604 = !DILocalVariable(name: "self", arg: 2, scope: !77, file: !1, line: 372, type: !5)
!605 = !DILocation(line: 372, column: 29, scope: !77)
!606 = !DILocalVariable(name: "standin", arg: 3, scope: !77, file: !1, line: 372, type: !5)
!607 = !DILocation(line: 372, column: 59, scope: !77)
!608 = !DILocalVariable(name: "standin_which", scope: !77, file: !1, line: 374, type: !63)
!609 = !DILocation(line: 374, column: 21, scope: !77)
!610 = !DILocation(line: 374, column: 37, scope: !77)
!611 = !DILocalVariable(name: "standin_other", scope: !77, file: !1, line: 375, type: !18)
!612 = !DILocation(line: 375, column: 15, scope: !77)
!613 = !DILocation(line: 375, column: 31, scope: !77)
!614 = !DILocation(line: 375, column: 45, scope: !77)
!615 = !DILocalVariable(name: "standin_son", scope: !77, file: !1, line: 376, type: !5)
!616 = !DILocation(line: 376, column: 26, scope: !77)
!617 = !DILocalVariable(name: "standin_father", scope: !77, file: !1, line: 377, type: !5)
!618 = !DILocation(line: 377, column: 26, scope: !77)
!619 = !DILocation(line: 377, column: 43, scope: !77)
!620 = !DILocalVariable(name: "rebalance", scope: !77, file: !1, line: 378, type: !38)
!621 = !DILocation(line: 378, column: 6, scope: !77)
!622 = !DILocation(line: 378, column: 18, scope: !77)
!623 = !DILocation(line: 378, column: 18, scope: !624)
!624 = !DILexicalBlockFile(scope: !77, file: !1, discriminator: 1)
!625 = !DILocation(line: 378, column: 18, scope: !626)
!626 = !DILexicalBlockFile(scope: !77, file: !1, discriminator: 2)
!627 = !DILocation(line: 378, column: 6, scope: !626)
!628 = !DILocation(line: 380, column: 6, scope: !629)
!629 = distinct !DILexicalBlock(scope: !77, file: !1, line: 380, column: 6)
!630 = !DILocation(line: 380, column: 24, scope: !629)
!631 = !DILocation(line: 380, column: 21, scope: !629)
!632 = !DILocation(line: 380, column: 6, scope: !77)
!633 = !DILocation(line: 385, column: 35, scope: !634)
!634 = distinct !DILexicalBlock(scope: !629, file: !1, line: 380, column: 30)
!635 = !DILocation(line: 385, column: 17, scope: !634)
!636 = !DILocation(line: 385, column: 26, scope: !634)
!637 = !DILocation(line: 385, column: 15, scope: !634)
!638 = !DILocation(line: 386, column: 2, scope: !634)
!639 = !DILocation(line: 391, column: 35, scope: !640)
!640 = distinct !DILexicalBlock(scope: !629, file: !1, line: 386, column: 9)
!641 = !DILocation(line: 391, column: 17, scope: !640)
!642 = !DILocation(line: 391, column: 26, scope: !640)
!643 = !DILocation(line: 391, column: 15, scope: !640)
!644 = !DILocation(line: 394, column: 6, scope: !645)
!645 = distinct !DILexicalBlock(scope: !77, file: !1, line: 394, column: 6)
!646 = !DILocation(line: 394, column: 6, scope: !647)
!647 = !DILexicalBlockFile(scope: !645, file: !1, discriminator: 1)
!648 = !DILocation(line: 399, column: 3, scope: !649)
!649 = distinct !DILexicalBlock(scope: !645, file: !1, line: 394, column: 29)
!650 = !DILocation(line: 400, column: 13, scope: !649)
!651 = !DILocation(line: 402, column: 7, scope: !652)
!652 = distinct !DILexicalBlock(scope: !649, file: !1, line: 402, column: 7)
!653 = !DILocation(line: 402, column: 25, scope: !652)
!654 = !DILocation(line: 402, column: 22, scope: !652)
!655 = !DILocation(line: 402, column: 7, scope: !649)
!656 = !DILocation(line: 406, column: 4, scope: !657)
!657 = distinct !DILexicalBlock(scope: !652, file: !1, line: 402, column: 31)
!658 = !DILocation(line: 407, column: 4, scope: !657)
!659 = !DILocation(line: 407, column: 4, scope: !660)
!660 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 1)
!661 = !DILocation(line: 407, column: 4, scope: !662)
!662 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 2)
!663 = !DILocation(line: 407, column: 4, scope: !664)
!664 = !DILexicalBlockFile(scope: !657, file: !1, discriminator: 3)
!665 = !DILocation(line: 408, column: 3, scope: !657)
!666 = !DILocation(line: 409, column: 2, scope: !649)
!667 = !DILocation(line: 411, column: 6, scope: !668)
!668 = distinct !DILexicalBlock(scope: !77, file: !1, line: 411, column: 6)
!669 = !DILocation(line: 411, column: 24, scope: !668)
!670 = !DILocation(line: 411, column: 21, scope: !668)
!671 = !DILocation(line: 411, column: 6, scope: !77)
!672 = !DILocation(line: 425, column: 20, scope: !673)
!673 = distinct !DILexicalBlock(scope: !668, file: !1, line: 411, column: 30)
!674 = !DILocation(line: 425, column: 18, scope: !673)
!675 = !DILocation(line: 426, column: 2, scope: !673)
!676 = !DILocation(line: 434, column: 45, scope: !677)
!677 = distinct !DILexicalBlock(scope: !668, file: !1, line: 426, column: 9)
!678 = !DILocation(line: 434, column: 28, scope: !677)
!679 = !DILocation(line: 434, column: 3, scope: !677)
!680 = !DILocation(line: 434, column: 19, scope: !677)
!681 = !DILocation(line: 434, column: 43, scope: !677)
!682 = !DILocation(line: 438, column: 53, scope: !677)
!683 = !DILocation(line: 438, column: 38, scope: !677)
!684 = !DILocation(line: 438, column: 44, scope: !677)
!685 = !DILocation(line: 438, column: 21, scope: !677)
!686 = !DILocation(line: 438, column: 3, scope: !677)
!687 = !DILocation(line: 438, column: 12, scope: !677)
!688 = !DILocation(line: 438, column: 36, scope: !677)
!689 = !DILocation(line: 439, column: 3, scope: !677)
!690 = !DILocation(line: 444, column: 19, scope: !677)
!691 = !DILocation(line: 444, column: 17, scope: !677)
!692 = !DILocation(line: 451, column: 52, scope: !77)
!693 = !DILocation(line: 451, column: 37, scope: !77)
!694 = !DILocation(line: 451, column: 43, scope: !77)
!695 = !DILocation(line: 451, column: 20, scope: !77)
!696 = !DILocation(line: 451, column: 2, scope: !77)
!697 = !DILocation(line: 451, column: 11, scope: !77)
!698 = !DILocation(line: 451, column: 35, scope: !77)
!699 = !DILocation(line: 452, column: 2, scope: !77)
!700 = !DILocation(line: 458, column: 2, scope: !77)
!701 = !DILocation(line: 459, column: 2, scope: !77)
!702 = !DILocation(line: 460, column: 55, scope: !77)
!703 = !DILocation(line: 460, column: 31, scope: !77)
!704 = !DILocation(line: 460, column: 2, scope: !77)
!705 = !DILocation(line: 460, column: 22, scope: !77)
!706 = !DILocation(line: 460, column: 53, scope: !77)
!707 = !DILocation(line: 462, column: 6, scope: !708)
!708 = distinct !DILexicalBlock(scope: !77, file: !1, line: 462, column: 6)
!709 = !DILocation(line: 462, column: 6, scope: !77)
!710 = !DILocation(line: 463, column: 39, scope: !708)
!711 = !DILocation(line: 463, column: 44, scope: !708)
!712 = !DILocation(line: 463, column: 60, scope: !708)
!713 = !DILocation(line: 463, column: 3, scope: !708)
!714 = !DILocation(line: 464, column: 1, scope: !77)
!715 = !DILocalVariable(name: "old_father", arg: 1, scope: !65, file: !1, line: 232, type: !5)
!716 = !DILocation(line: 232, column: 29, scope: !65)
!717 = !DILocalVariable(name: "which", arg: 2, scope: !65, file: !1, line: 232, type: !63)
!718 = !DILocation(line: 232, column: 60, scope: !65)
!719 = !DILocalVariable(name: "other", scope: !65, file: !1, line: 234, type: !63)
!720 = !DILocation(line: 234, column: 21, scope: !65)
!721 = !DILocation(line: 234, column: 29, scope: !65)
!722 = !DILocation(line: 234, column: 35, scope: !65)
!723 = !DILocalVariable(name: "grandpa", scope: !65, file: !1, line: 235, type: !724)
!724 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !5)
!725 = !DILocation(line: 235, column: 33, scope: !65)
!726 = !DILocation(line: 235, column: 43, scope: !65)
!727 = !DILocalVariable(name: "old_child", scope: !65, file: !1, line: 236, type: !724)
!728 = !DILocation(line: 236, column: 33, scope: !65)
!729 = !DILocation(line: 236, column: 66, scope: !65)
!730 = !DILocation(line: 236, column: 45, scope: !65)
!731 = !DILocation(line: 236, column: 57, scope: !65)
!732 = !DILocalVariable(name: "new_father", scope: !65, file: !1, line: 237, type: !724)
!733 = !DILocation(line: 237, column: 33, scope: !65)
!734 = !DILocation(line: 237, column: 46, scope: !65)
!735 = !DILocalVariable(name: "new_child", scope: !65, file: !1, line: 238, type: !724)
!736 = !DILocation(line: 238, column: 33, scope: !65)
!737 = !DILocation(line: 238, column: 45, scope: !65)
!738 = !DILocation(line: 240, column: 6, scope: !739)
!739 = distinct !DILexicalBlock(scope: !65, file: !1, line: 240, column: 6)
!740 = !DILocation(line: 240, column: 17, scope: !739)
!741 = !DILocation(line: 240, column: 6, scope: !65)
!742 = !DILocation(line: 241, column: 3, scope: !739)
!743 = !DILocation(line: 245, column: 47, scope: !65)
!744 = !DILocation(line: 245, column: 20, scope: !65)
!745 = !DILocation(line: 245, column: 2, scope: !65)
!746 = !DILocation(line: 245, column: 11, scope: !65)
!747 = !DILocation(line: 245, column: 45, scope: !65)
!748 = !DILocation(line: 246, column: 51, scope: !65)
!749 = !DILocation(line: 246, column: 31, scope: !65)
!750 = !DILocation(line: 246, column: 42, scope: !65)
!751 = !DILocation(line: 246, column: 22, scope: !65)
!752 = !DILocation(line: 246, column: 2, scope: !65)
!753 = !DILocation(line: 246, column: 13, scope: !65)
!754 = !DILocation(line: 246, column: 29, scope: !65)
!755 = !DILocation(line: 247, column: 32, scope: !65)
!756 = !DILocation(line: 247, column: 23, scope: !65)
!757 = !DILocation(line: 247, column: 2, scope: !65)
!758 = !DILocation(line: 247, column: 14, scope: !65)
!759 = !DILocation(line: 247, column: 30, scope: !65)
!760 = !DILocation(line: 252, column: 2, scope: !65)
!761 = !DILocation(line: 253, column: 2, scope: !65)
!762 = !DILocation(line: 259, column: 2, scope: !65)
!763 = !DILocalVariable(name: "xorinfo", scope: !764, file: !1, line: 259, type: !14)
!764 = distinct !DILexicalBlock(scope: !65, file: !1, line: 259, column: 2)
!765 = !DILocation(line: 259, column: 2, scope: !764)
!766 = !DILocation(line: 259, column: 2, scope: !767)
!767 = !DILexicalBlockFile(scope: !764, file: !1, discriminator: 1)
!768 = !DILocation(line: 260, column: 2, scope: !65)
!769 = !DILocation(line: 260, column: 2, scope: !770)
!770 = !DILexicalBlockFile(scope: !65, file: !1, discriminator: 1)
!771 = !DILocation(line: 260, column: 2, scope: !772)
!772 = !DILexicalBlockFile(scope: !65, file: !1, discriminator: 2)
!773 = !DILocation(line: 260, column: 2, scope: !774)
!774 = !DILexicalBlockFile(scope: !65, file: !1, discriminator: 3)
!775 = !DILocation(line: 265, column: 7, scope: !776)
!776 = distinct !DILexicalBlock(scope: !65, file: !1, line: 265, column: 6)
!777 = !DILocation(line: 265, column: 6, scope: !65)
!778 = !DILocation(line: 266, column: 3, scope: !779)
!779 = distinct !DILexicalBlock(scope: !776, file: !1, line: 265, column: 50)
!780 = !DILocation(line: 267, column: 3, scope: !779)
!781 = !DILocation(line: 267, column: 3, scope: !782)
!782 = !DILexicalBlockFile(scope: !779, file: !1, discriminator: 1)
!783 = !DILocation(line: 267, column: 3, scope: !784)
!784 = !DILexicalBlockFile(scope: !779, file: !1, discriminator: 2)
!785 = !DILocation(line: 267, column: 3, scope: !786)
!786 = !DILexicalBlockFile(scope: !779, file: !1, discriminator: 3)
!787 = !DILocation(line: 268, column: 2, scope: !779)
!788 = !DILocation(line: 270, column: 1, scope: !65)
!789 = !DILocalVariable(name: "rbt", arg: 1, scope: !71, file: !1, line: 549, type: !23)
!790 = !DILocation(line: 549, column: 61, scope: !71)
!791 = !DILocalVariable(name: "parent", arg: 2, scope: !71, file: !1, line: 550, type: !5)
!792 = !DILocation(line: 550, column: 29, scope: !71)
!793 = !DILocalVariable(name: "which", arg: 3, scope: !71, file: !1, line: 550, type: !18)
!794 = !DILocation(line: 550, column: 50, scope: !71)
!795 = !DILocation(line: 553, column: 2, scope: !71)
!796 = !DILocation(line: 553, column: 9, scope: !797)
!797 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 1)
!798 = !DILocation(line: 553, column: 9, scope: !799)
!799 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 2)
!800 = !DILocation(line: 553, column: 2, scope: !801)
!801 = !DILexicalBlockFile(scope: !71, file: !1, discriminator: 3)
!802 = !DILocalVariable(name: "other", scope: !803, file: !1, line: 554, type: !18)
!803 = distinct !DILexicalBlock(scope: !71, file: !1, line: 553, column: 46)
!804 = !DILocation(line: 554, column: 16, scope: !803)
!805 = !DILocation(line: 554, column: 24, scope: !803)
!806 = !DILocation(line: 554, column: 30, scope: !803)
!807 = !DILocalVariable(name: "brother", scope: !803, file: !1, line: 555, type: !5)
!808 = !DILocation(line: 555, column: 27, scope: !803)
!809 = !DILocation(line: 555, column: 54, scope: !803)
!810 = !DILocation(line: 555, column: 37, scope: !803)
!811 = !DILocation(line: 555, column: 45, scope: !803)
!812 = !DILocation(line: 557, column: 7, scope: !813)
!813 = distinct !DILexicalBlock(scope: !803, file: !1, line: 557, column: 7)
!814 = !DILocation(line: 557, column: 15, scope: !813)
!815 = !DILocation(line: 557, column: 7, scope: !803)
!816 = !DILocation(line: 558, column: 4, scope: !813)
!817 = !DILocation(line: 563, column: 7, scope: !818)
!818 = distinct !DILexicalBlock(scope: !803, file: !1, line: 563, column: 7)
!819 = !DILocation(line: 563, column: 7, scope: !820)
!820 = !DILexicalBlockFile(scope: !818, file: !1, discriminator: 1)
!821 = !DILocation(line: 564, column: 7, scope: !818)
!822 = !DILocation(line: 564, column: 10, scope: !820)
!823 = !DILocation(line: 564, column: 10, scope: !824)
!824 = !DILexicalBlockFile(scope: !818, file: !1, discriminator: 2)
!825 = !DILocation(line: 565, column: 7, scope: !818)
!826 = !DILocation(line: 565, column: 10, scope: !820)
!827 = !DILocation(line: 565, column: 10, scope: !824)
!828 = !DILocation(line: 563, column: 7, scope: !829)
!829 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 2)
!830 = !DILocation(line: 566, column: 8, scope: !831)
!831 = distinct !DILexicalBlock(scope: !832, file: !1, line: 566, column: 8)
!832 = distinct !DILexicalBlock(scope: !818, file: !1, line: 565, column: 41)
!833 = !DILocation(line: 566, column: 8, scope: !834)
!834 = !DILexicalBlockFile(scope: !831, file: !1, discriminator: 1)
!835 = !DILocation(line: 578, column: 38, scope: !836)
!836 = distinct !DILexicalBlock(scope: !831, file: !1, line: 566, column: 27)
!837 = !DILocation(line: 578, column: 46, scope: !836)
!838 = !DILocation(line: 578, column: 5, scope: !836)
!839 = !DILocation(line: 579, column: 32, scope: !836)
!840 = !DILocation(line: 579, column: 15, scope: !836)
!841 = !DILocation(line: 579, column: 23, scope: !836)
!842 = !DILocation(line: 579, column: 13, scope: !836)
!843 = !DILocation(line: 580, column: 9, scope: !844)
!844 = distinct !DILexicalBlock(scope: !836, file: !1, line: 580, column: 9)
!845 = !DILocation(line: 580, column: 17, scope: !844)
!846 = !DILocation(line: 580, column: 9, scope: !836)
!847 = !DILocation(line: 581, column: 6, scope: !844)
!848 = !DILocation(line: 582, column: 4, scope: !836)
!849 = !DILocation(line: 592, column: 5, scope: !850)
!850 = distinct !DILexicalBlock(scope: !831, file: !1, line: 582, column: 11)
!851 = !DILocation(line: 593, column: 9, scope: !852)
!852 = distinct !DILexicalBlock(scope: !850, file: !1, line: 593, column: 9)
!853 = !DILocation(line: 593, column: 9, scope: !850)
!854 = !DILocation(line: 594, column: 6, scope: !852)
!855 = !DILocation(line: 595, column: 13, scope: !850)
!856 = !DILocation(line: 595, column: 11, scope: !850)
!857 = !DILocation(line: 596, column: 14, scope: !850)
!858 = !DILocation(line: 596, column: 12, scope: !850)
!859 = !DILocation(line: 597, column: 5, scope: !850)
!860 = !DILocation(line: 599, column: 3, scope: !832)
!861 = !DILocation(line: 604, column: 7, scope: !862)
!862 = distinct !DILexicalBlock(scope: !803, file: !1, line: 604, column: 7)
!863 = !DILocation(line: 604, column: 7, scope: !864)
!864 = !DILexicalBlockFile(scope: !862, file: !1, discriminator: 1)
!865 = !DILocation(line: 605, column: 7, scope: !862)
!866 = !DILocation(line: 605, column: 10, scope: !864)
!867 = !DILocation(line: 605, column: 10, scope: !868)
!868 = !DILexicalBlockFile(scope: !862, file: !1, discriminator: 2)
!869 = !DILocation(line: 606, column: 7, scope: !862)
!870 = !DILocation(line: 606, column: 10, scope: !864)
!871 = !DILocation(line: 606, column: 10, scope: !868)
!872 = !DILocation(line: 607, column: 7, scope: !862)
!873 = !DILocation(line: 607, column: 10, scope: !864)
!874 = !DILocation(line: 607, column: 10, scope: !868)
!875 = !DILocation(line: 604, column: 7, scope: !829)
!876 = !DILocation(line: 618, column: 4, scope: !877)
!877 = distinct !DILexicalBlock(scope: !862, file: !1, line: 607, column: 41)
!878 = !DILocation(line: 619, column: 4, scope: !877)
!879 = !DILocation(line: 620, column: 4, scope: !877)
!880 = !DILocation(line: 626, column: 8, scope: !881)
!881 = distinct !DILexicalBlock(scope: !882, file: !1, line: 626, column: 8)
!882 = distinct !DILexicalBlock(scope: !862, file: !1, line: 621, column: 10)
!883 = !DILocation(line: 626, column: 8, scope: !884)
!884 = !DILexicalBlockFile(scope: !881, file: !1, discriminator: 1)
!885 = !DILocation(line: 638, column: 38, scope: !886)
!886 = distinct !DILexicalBlock(scope: !881, file: !1, line: 626, column: 46)
!887 = !DILocation(line: 638, column: 47, scope: !886)
!888 = !DILocation(line: 638, column: 5, scope: !886)
!889 = !DILocation(line: 639, column: 32, scope: !886)
!890 = !DILocation(line: 639, column: 15, scope: !886)
!891 = !DILocation(line: 639, column: 23, scope: !886)
!892 = !DILocation(line: 639, column: 13, scope: !886)
!893 = !DILocation(line: 640, column: 4, scope: !886)
!894 = !DILocation(line: 665, column: 26, scope: !895)
!895 = distinct !DILexicalBlock(scope: !882, file: !1, line: 665, column: 8)
!896 = !DILocation(line: 665, column: 8, scope: !895)
!897 = !DILocation(line: 665, column: 17, scope: !895)
!898 = !DILocation(line: 665, column: 33, scope: !895)
!899 = !DILocation(line: 665, column: 8, scope: !882)
!900 = !DILocation(line: 666, column: 5, scope: !895)
!901 = !DILocation(line: 667, column: 4, scope: !882)
!902 = !DILocation(line: 668, column: 37, scope: !882)
!903 = !DILocation(line: 668, column: 45, scope: !882)
!904 = !DILocation(line: 668, column: 4, scope: !882)
!905 = !DILocation(line: 669, column: 4, scope: !882)
!906 = !DILocation(line: 672, column: 1, scope: !71)
