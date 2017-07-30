; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_set_standard_lookup.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type opaque
%struct.name_cache = type { %struct.archive*, i8*, i64, i32, i32, i64, [127 x %struct.anon] }
%struct.anon = type { i32, i8* }
%struct.passwd = type { i8*, i8*, i32, i32, i8*, i8*, i8* }
%struct.group = type { i8*, i8*, i32, i8** }

@.str = private unnamed_addr constant [40 x i8] c"Can't allocate uname/gname lookup cache\00", align 1
@NO_NAME = internal constant i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.1, i32 0, i32 0), align 8
@.str.1 = private unnamed_addr constant [9 x i8] c"(noname)\00", align 1
@.str.2 = private unnamed_addr constant [28 x i8] c"Can't lookup user for id %d\00", align 1
@.str.3 = private unnamed_addr constant [29 x i8] c"Can't lookup group for id %d\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_standard_lookup(%struct.archive* %a) #0 !dbg !45 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %ucache = alloca %struct.name_cache*, align 8
  %gcache = alloca %struct.name_cache*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !71, metadata !72), !dbg !73
  call void @llvm.dbg.declare(metadata %struct.name_cache** %ucache, metadata !74, metadata !72), !dbg !75
  %call = call noalias i8* @malloc(i64 2072) #6, !dbg !76
  %0 = bitcast i8* %call to %struct.name_cache*, !dbg !76
  store %struct.name_cache* %0, %struct.name_cache** %ucache, align 8, !dbg !75
  call void @llvm.dbg.declare(metadata %struct.name_cache** %gcache, metadata !77, metadata !72), !dbg !78
  %call1 = call noalias i8* @malloc(i64 2072) #6, !dbg !79
  %1 = bitcast i8* %call1 to %struct.name_cache*, !dbg !79
  store %struct.name_cache* %1, %struct.name_cache** %gcache, align 8, !dbg !78
  %2 = load %struct.name_cache*, %struct.name_cache** %ucache, align 8, !dbg !80
  %cmp = icmp eq %struct.name_cache* %2, null, !dbg !82
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !83

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.name_cache*, %struct.name_cache** %gcache, align 8, !dbg !84
  %cmp2 = icmp eq %struct.name_cache* %3, null, !dbg !86
  br i1 %cmp2, label %if.then, label %if.end, !dbg !87

if.then:                                          ; preds = %lor.lhs.false, %entry
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !88
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %4, i32 12, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str, i32 0, i32 0)), !dbg !90
  %5 = load %struct.name_cache*, %struct.name_cache** %ucache, align 8, !dbg !91
  %6 = bitcast %struct.name_cache* %5 to i8*, !dbg !91
  call void @free(i8* %6) #6, !dbg !92
  %7 = load %struct.name_cache*, %struct.name_cache** %gcache, align 8, !dbg !93
  %8 = bitcast %struct.name_cache* %7 to i8*, !dbg !93
  call void @free(i8* %8) #6, !dbg !94
  store i32 -30, i32* %retval, align 4, !dbg !95
  br label %return, !dbg !95

if.end:                                           ; preds = %lor.lhs.false
  %9 = load %struct.name_cache*, %struct.name_cache** %ucache, align 8, !dbg !96
  %10 = bitcast %struct.name_cache* %9 to i8*, !dbg !97
  call void @llvm.memset.p0i8.i64(i8* %10, i8 0, i64 2072, i32 8, i1 false), !dbg !97
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !98
  %12 = load %struct.name_cache*, %struct.name_cache** %ucache, align 8, !dbg !99
  %archive = getelementptr inbounds %struct.name_cache, %struct.name_cache* %12, i32 0, i32 0, !dbg !100
  store %struct.archive* %11, %struct.archive** %archive, align 8, !dbg !101
  %13 = load %struct.name_cache*, %struct.name_cache** %ucache, align 8, !dbg !102
  %size = getelementptr inbounds %struct.name_cache, %struct.name_cache* %13, i32 0, i32 5, !dbg !103
  store i64 127, i64* %size, align 8, !dbg !104
  %14 = load %struct.name_cache*, %struct.name_cache** %gcache, align 8, !dbg !105
  %15 = bitcast %struct.name_cache* %14 to i8*, !dbg !106
  call void @llvm.memset.p0i8.i64(i8* %15, i8 0, i64 2072, i32 8, i1 false), !dbg !106
  %16 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !107
  %17 = load %struct.name_cache*, %struct.name_cache** %gcache, align 8, !dbg !108
  %archive3 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %17, i32 0, i32 0, !dbg !109
  store %struct.archive* %16, %struct.archive** %archive3, align 8, !dbg !110
  %18 = load %struct.name_cache*, %struct.name_cache** %gcache, align 8, !dbg !111
  %size4 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %18, i32 0, i32 5, !dbg !112
  store i64 127, i64* %size4, align 8, !dbg !113
  %19 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !114
  %20 = load %struct.name_cache*, %struct.name_cache** %gcache, align 8, !dbg !115
  %21 = bitcast %struct.name_cache* %20 to i8*, !dbg !115
  %call5 = call i32 @archive_read_disk_set_gname_lookup(%struct.archive* %19, i8* %21, i8* (i8*, i64)* @lookup_gname, void (i8*)* @cleanup), !dbg !116
  %22 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !117
  %23 = load %struct.name_cache*, %struct.name_cache** %ucache, align 8, !dbg !118
  %24 = bitcast %struct.name_cache* %23 to i8*, !dbg !118
  %call6 = call i32 @archive_read_disk_set_uname_lookup(%struct.archive* %22, i8* %24, i8* (i8*, i64)* @lookup_uname, void (i8*)* @cleanup), !dbg !119
  store i32 0, i32* %retval, align 4, !dbg !120
  br label %return, !dbg !120

return:                                           ; preds = %if.end, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !121
  ret i32 %25, !dbg !121
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

declare i32 @archive_read_disk_set_gname_lookup(%struct.archive*, i8*, i8* (i8*, i64)*, void (i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i8* @lookup_gname(i8* %data, i64 %gid) #0 !dbg !63 {
entry:
  %data.addr = alloca i8*, align 8
  %gid.addr = alloca i64, align 8
  %gname_cache = alloca %struct.name_cache*, align 8
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !122, metadata !72), !dbg !123
  store i64 %gid, i64* %gid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %gid.addr, metadata !124, metadata !72), !dbg !125
  call void @llvm.dbg.declare(metadata %struct.name_cache** %gname_cache, metadata !126, metadata !72), !dbg !127
  %0 = load i8*, i8** %data.addr, align 8, !dbg !128
  %1 = bitcast i8* %0 to %struct.name_cache*, !dbg !129
  store %struct.name_cache* %1, %struct.name_cache** %gname_cache, align 8, !dbg !127
  %2 = load %struct.name_cache*, %struct.name_cache** %gname_cache, align 8, !dbg !130
  %3 = load i64, i64* %gid.addr, align 8, !dbg !131
  %conv = trunc i64 %3 to i32, !dbg !132
  %call = call i8* @lookup_name(%struct.name_cache* %2, i8* (%struct.name_cache*, i32)* @lookup_gname_helper, i32 %conv), !dbg !133
  ret i8* %call, !dbg !134
}

; Function Attrs: nounwind uwtable
define internal void @cleanup(i8* %data) #0 !dbg !48 {
entry:
  %data.addr = alloca i8*, align 8
  %cache = alloca %struct.name_cache*, align 8
  %i = alloca i64, align 8
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !135, metadata !72), !dbg !136
  call void @llvm.dbg.declare(metadata %struct.name_cache** %cache, metadata !137, metadata !72), !dbg !138
  %0 = load i8*, i8** %data.addr, align 8, !dbg !139
  %1 = bitcast i8* %0 to %struct.name_cache*, !dbg !140
  store %struct.name_cache* %1, %struct.name_cache** %cache, align 8, !dbg !138
  call void @llvm.dbg.declare(metadata i64* %i, metadata !141, metadata !72), !dbg !142
  %2 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !143
  %cmp = icmp ne %struct.name_cache* %2, null, !dbg !145
  br i1 %cmp, label %if.then, label %if.end12, !dbg !146

if.then:                                          ; preds = %entry
  store i64 0, i64* %i, align 8, !dbg !147
  br label %for.cond, !dbg !150

for.cond:                                         ; preds = %for.inc, %if.then
  %3 = load i64, i64* %i, align 8, !dbg !151
  %4 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !154
  %size = getelementptr inbounds %struct.name_cache, %struct.name_cache* %4, i32 0, i32 5, !dbg !155
  %5 = load i64, i64* %size, align 8, !dbg !155
  %cmp1 = icmp ult i64 %3, %5, !dbg !156
  br i1 %cmp1, label %for.body, label %for.end, !dbg !157

for.body:                                         ; preds = %for.cond
  %6 = load i64, i64* %i, align 8, !dbg !158
  %7 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !161
  %cache2 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %7, i32 0, i32 6, !dbg !162
  %arrayidx = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache2, i64 0, i64 %6, !dbg !161
  %name = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 1, !dbg !163
  %8 = load i8*, i8** %name, align 8, !dbg !163
  %cmp3 = icmp ne i8* %8, null, !dbg !164
  br i1 %cmp3, label %land.lhs.true, label %if.end, !dbg !165

land.lhs.true:                                    ; preds = %for.body
  %9 = load i64, i64* %i, align 8, !dbg !166
  %10 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !167
  %cache4 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %10, i32 0, i32 6, !dbg !168
  %arrayidx5 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache4, i64 0, i64 %9, !dbg !167
  %name6 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx5, i32 0, i32 1, !dbg !169
  %11 = load i8*, i8** %name6, align 8, !dbg !169
  %12 = load i8*, i8** @NO_NAME, align 8, !dbg !170
  %cmp7 = icmp ne i8* %11, %12, !dbg !171
  br i1 %cmp7, label %if.then8, label %if.end, !dbg !172

if.then8:                                         ; preds = %land.lhs.true
  %13 = load i64, i64* %i, align 8, !dbg !174
  %14 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !175
  %cache9 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %14, i32 0, i32 6, !dbg !176
  %arrayidx10 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache9, i64 0, i64 %13, !dbg !175
  %name11 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx10, i32 0, i32 1, !dbg !177
  %15 = load i8*, i8** %name11, align 8, !dbg !177
  %16 = ptrtoint i8* %15 to i64, !dbg !178
  %17 = inttoptr i64 %16 to i8*, !dbg !179
  call void @free(i8* %17) #6, !dbg !180
  br label %if.end, !dbg !180

if.end:                                           ; preds = %if.then8, %land.lhs.true, %for.body
  br label %for.inc, !dbg !181

for.inc:                                          ; preds = %if.end
  %18 = load i64, i64* %i, align 8, !dbg !182
  %inc = add i64 %18, 1, !dbg !182
  store i64 %inc, i64* %i, align 8, !dbg !182
  br label %for.cond, !dbg !184

for.end:                                          ; preds = %for.cond
  %19 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !185
  %buff = getelementptr inbounds %struct.name_cache, %struct.name_cache* %19, i32 0, i32 1, !dbg !186
  %20 = load i8*, i8** %buff, align 8, !dbg !186
  call void @free(i8* %20) #6, !dbg !187
  %21 = load %struct.name_cache*, %struct.name_cache** %cache, align 8, !dbg !188
  %22 = bitcast %struct.name_cache* %21 to i8*, !dbg !188
  call void @free(i8* %22) #6, !dbg !189
  br label %if.end12, !dbg !190

if.end12:                                         ; preds = %for.end, %entry
  ret void, !dbg !191
}

declare i32 @archive_read_disk_set_uname_lookup(%struct.archive*, i8*, i8* (i8*, i64)*, void (i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i8* @lookup_uname(i8* %data, i64 %uid) #0 !dbg !51 {
entry:
  %data.addr = alloca i8*, align 8
  %uid.addr = alloca i64, align 8
  %uname_cache = alloca %struct.name_cache*, align 8
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !192, metadata !72), !dbg !193
  store i64 %uid, i64* %uid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uid.addr, metadata !194, metadata !72), !dbg !195
  call void @llvm.dbg.declare(metadata %struct.name_cache** %uname_cache, metadata !196, metadata !72), !dbg !197
  %0 = load i8*, i8** %data.addr, align 8, !dbg !198
  %1 = bitcast i8* %0 to %struct.name_cache*, !dbg !199
  store %struct.name_cache* %1, %struct.name_cache** %uname_cache, align 8, !dbg !197
  %2 = load %struct.name_cache*, %struct.name_cache** %uname_cache, align 8, !dbg !200
  %3 = load i64, i64* %uid.addr, align 8, !dbg !201
  %conv = trunc i64 %3 to i32, !dbg !202
  %call = call i8* @lookup_name(%struct.name_cache* %2, i8* (%struct.name_cache*, i32)* @lookup_uname_helper, i32 %conv), !dbg !203
  ret i8* %call, !dbg !204
}

; Function Attrs: nounwind uwtable
define internal i8* @lookup_name(%struct.name_cache* %cache, i8* (%struct.name_cache*, i32)* %lookup_fn, i32 %id) #0 !dbg !56 {
entry:
  %retval = alloca i8*, align 8
  %cache.addr = alloca %struct.name_cache*, align 8
  %lookup_fn.addr = alloca i8* (%struct.name_cache*, i32)*, align 8
  %id.addr = alloca i32, align 4
  %name = alloca i8*, align 8
  %slot = alloca i32, align 4
  store %struct.name_cache* %cache, %struct.name_cache** %cache.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.name_cache** %cache.addr, metadata !205, metadata !72), !dbg !206
  store i8* (%struct.name_cache*, i32)* %lookup_fn, i8* (%struct.name_cache*, i32)** %lookup_fn.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (%struct.name_cache*, i32)** %lookup_fn.addr, metadata !207, metadata !72), !dbg !208
  store i32 %id, i32* %id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %id.addr, metadata !209, metadata !72), !dbg !210
  call void @llvm.dbg.declare(metadata i8** %name, metadata !211, metadata !72), !dbg !212
  call void @llvm.dbg.declare(metadata i32* %slot, metadata !213, metadata !72), !dbg !214
  %0 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !215
  %probes = getelementptr inbounds %struct.name_cache, %struct.name_cache* %0, i32 0, i32 3, !dbg !216
  %1 = load i32, i32* %probes, align 8, !dbg !217
  %inc = add nsw i32 %1, 1, !dbg !217
  store i32 %inc, i32* %probes, align 8, !dbg !217
  %2 = load i32, i32* %id.addr, align 4, !dbg !218
  %conv = zext i32 %2 to i64, !dbg !218
  %3 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !219
  %size = getelementptr inbounds %struct.name_cache, %struct.name_cache* %3, i32 0, i32 5, !dbg !220
  %4 = load i64, i64* %size, align 8, !dbg !220
  %rem = urem i64 %conv, %4, !dbg !221
  %conv1 = trunc i64 %rem to i32, !dbg !218
  store i32 %conv1, i32* %slot, align 4, !dbg !222
  %5 = load i32, i32* %slot, align 4, !dbg !223
  %idxprom = sext i32 %5 to i64, !dbg !225
  %6 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !225
  %cache2 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %6, i32 0, i32 6, !dbg !226
  %arrayidx = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache2, i64 0, i64 %idxprom, !dbg !225
  %name3 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 1, !dbg !227
  %7 = load i8*, i8** %name3, align 8, !dbg !227
  %cmp = icmp ne i8* %7, null, !dbg !228
  br i1 %cmp, label %if.then, label %if.end41, !dbg !229

if.then:                                          ; preds = %entry
  %8 = load i32, i32* %slot, align 4, !dbg !230
  %idxprom5 = sext i32 %8 to i64, !dbg !233
  %9 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !233
  %cache6 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %9, i32 0, i32 6, !dbg !234
  %arrayidx7 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache6, i64 0, i64 %idxprom5, !dbg !233
  %id8 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx7, i32 0, i32 0, !dbg !235
  %10 = load i32, i32* %id8, align 8, !dbg !235
  %11 = load i32, i32* %id.addr, align 4, !dbg !236
  %cmp9 = icmp eq i32 %10, %11, !dbg !237
  br i1 %cmp9, label %if.then11, label %if.end24, !dbg !238

if.then11:                                        ; preds = %if.then
  %12 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !239
  %hits = getelementptr inbounds %struct.name_cache, %struct.name_cache* %12, i32 0, i32 4, !dbg !241
  %13 = load i32, i32* %hits, align 4, !dbg !242
  %inc12 = add nsw i32 %13, 1, !dbg !242
  store i32 %inc12, i32* %hits, align 4, !dbg !242
  %14 = load i32, i32* %slot, align 4, !dbg !243
  %idxprom13 = sext i32 %14 to i64, !dbg !245
  %15 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !245
  %cache14 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %15, i32 0, i32 6, !dbg !246
  %arrayidx15 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache14, i64 0, i64 %idxprom13, !dbg !245
  %name16 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx15, i32 0, i32 1, !dbg !247
  %16 = load i8*, i8** %name16, align 8, !dbg !247
  %17 = load i8*, i8** @NO_NAME, align 8, !dbg !248
  %cmp17 = icmp eq i8* %16, %17, !dbg !249
  br i1 %cmp17, label %if.then19, label %if.end, !dbg !250

if.then19:                                        ; preds = %if.then11
  store i8* null, i8** %retval, align 8, !dbg !251
  br label %return, !dbg !251

if.end:                                           ; preds = %if.then11
  %18 = load i32, i32* %slot, align 4, !dbg !252
  %idxprom20 = sext i32 %18 to i64, !dbg !253
  %19 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !253
  %cache21 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %19, i32 0, i32 6, !dbg !254
  %arrayidx22 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache21, i64 0, i64 %idxprom20, !dbg !253
  %name23 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx22, i32 0, i32 1, !dbg !255
  %20 = load i8*, i8** %name23, align 8, !dbg !255
  store i8* %20, i8** %retval, align 8, !dbg !256
  br label %return, !dbg !256

if.end24:                                         ; preds = %if.then
  %21 = load i32, i32* %slot, align 4, !dbg !257
  %idxprom25 = sext i32 %21 to i64, !dbg !259
  %22 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !259
  %cache26 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %22, i32 0, i32 6, !dbg !260
  %arrayidx27 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache26, i64 0, i64 %idxprom25, !dbg !259
  %name28 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx27, i32 0, i32 1, !dbg !261
  %23 = load i8*, i8** %name28, align 8, !dbg !261
  %24 = load i8*, i8** @NO_NAME, align 8, !dbg !262
  %cmp29 = icmp ne i8* %23, %24, !dbg !263
  br i1 %cmp29, label %if.then31, label %if.end36, !dbg !264

if.then31:                                        ; preds = %if.end24
  %25 = load i32, i32* %slot, align 4, !dbg !265
  %idxprom32 = sext i32 %25 to i64, !dbg !266
  %26 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !266
  %cache33 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %26, i32 0, i32 6, !dbg !267
  %arrayidx34 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache33, i64 0, i64 %idxprom32, !dbg !266
  %name35 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx34, i32 0, i32 1, !dbg !268
  %27 = load i8*, i8** %name35, align 8, !dbg !268
  %28 = ptrtoint i8* %27 to i64, !dbg !269
  %29 = inttoptr i64 %28 to i8*, !dbg !270
  call void @free(i8* %29) #6, !dbg !271
  br label %if.end36, !dbg !271

if.end36:                                         ; preds = %if.then31, %if.end24
  %30 = load i32, i32* %slot, align 4, !dbg !272
  %idxprom37 = sext i32 %30 to i64, !dbg !273
  %31 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !273
  %cache38 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %31, i32 0, i32 6, !dbg !274
  %arrayidx39 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache38, i64 0, i64 %idxprom37, !dbg !273
  %name40 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx39, i32 0, i32 1, !dbg !275
  store i8* null, i8** %name40, align 8, !dbg !276
  br label %if.end41, !dbg !277

if.end41:                                         ; preds = %if.end36, %entry
  %32 = load i8* (%struct.name_cache*, i32)*, i8* (%struct.name_cache*, i32)** %lookup_fn.addr, align 8, !dbg !278
  %33 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !279
  %34 = load i32, i32* %id.addr, align 4, !dbg !280
  %call = call i8* %32(%struct.name_cache* %33, i32 %34), !dbg !281
  store i8* %call, i8** %name, align 8, !dbg !282
  %35 = load i8*, i8** %name, align 8, !dbg !283
  %cmp42 = icmp eq i8* %35, null, !dbg !285
  br i1 %cmp42, label %if.then44, label %if.end53, !dbg !286

if.then44:                                        ; preds = %if.end41
  %36 = load i8*, i8** @NO_NAME, align 8, !dbg !287
  %37 = load i32, i32* %slot, align 4, !dbg !289
  %idxprom45 = sext i32 %37 to i64, !dbg !290
  %38 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !290
  %cache46 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %38, i32 0, i32 6, !dbg !291
  %arrayidx47 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache46, i64 0, i64 %idxprom45, !dbg !290
  %name48 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx47, i32 0, i32 1, !dbg !292
  store i8* %36, i8** %name48, align 8, !dbg !293
  %39 = load i32, i32* %id.addr, align 4, !dbg !294
  %40 = load i32, i32* %slot, align 4, !dbg !295
  %idxprom49 = sext i32 %40 to i64, !dbg !296
  %41 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !296
  %cache50 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %41, i32 0, i32 6, !dbg !297
  %arrayidx51 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache50, i64 0, i64 %idxprom49, !dbg !296
  %id52 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx51, i32 0, i32 0, !dbg !298
  store i32 %39, i32* %id52, align 8, !dbg !299
  store i8* null, i8** %retval, align 8, !dbg !300
  br label %return, !dbg !300

if.end53:                                         ; preds = %if.end41
  %42 = load i8*, i8** %name, align 8, !dbg !301
  %43 = load i32, i32* %slot, align 4, !dbg !302
  %idxprom54 = sext i32 %43 to i64, !dbg !303
  %44 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !303
  %cache55 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %44, i32 0, i32 6, !dbg !304
  %arrayidx56 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache55, i64 0, i64 %idxprom54, !dbg !303
  %name57 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx56, i32 0, i32 1, !dbg !305
  store i8* %42, i8** %name57, align 8, !dbg !306
  %45 = load i32, i32* %id.addr, align 4, !dbg !307
  %46 = load i32, i32* %slot, align 4, !dbg !308
  %idxprom58 = sext i32 %46 to i64, !dbg !309
  %47 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !309
  %cache59 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %47, i32 0, i32 6, !dbg !310
  %arrayidx60 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache59, i64 0, i64 %idxprom58, !dbg !309
  %id61 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx60, i32 0, i32 0, !dbg !311
  store i32 %45, i32* %id61, align 8, !dbg !312
  %48 = load i32, i32* %slot, align 4, !dbg !313
  %idxprom62 = sext i32 %48 to i64, !dbg !314
  %49 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !314
  %cache63 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %49, i32 0, i32 6, !dbg !315
  %arrayidx64 = getelementptr inbounds [127 x %struct.anon], [127 x %struct.anon]* %cache63, i64 0, i64 %idxprom62, !dbg !314
  %name65 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx64, i32 0, i32 1, !dbg !316
  %50 = load i8*, i8** %name65, align 8, !dbg !316
  store i8* %50, i8** %retval, align 8, !dbg !317
  br label %return, !dbg !317

return:                                           ; preds = %if.end53, %if.then44, %if.end, %if.then19
  %51 = load i8*, i8** %retval, align 8, !dbg !318
  ret i8* %51, !dbg !318
}

; Function Attrs: nounwind uwtable
define internal i8* @lookup_uname_helper(%struct.name_cache* %cache, i32 %id) #0 !dbg !62 {
entry:
  %retval = alloca i8*, align 8
  %cache.addr = alloca %struct.name_cache*, align 8
  %id.addr = alloca i32, align 4
  %pwent = alloca %struct.passwd, align 8
  %result = alloca %struct.passwd*, align 8
  %nbuff = alloca i8*, align 8
  %nbuff_size = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.name_cache* %cache, %struct.name_cache** %cache.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.name_cache** %cache.addr, metadata !319, metadata !72), !dbg !320
  store i32 %id, i32* %id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %id.addr, metadata !321, metadata !72), !dbg !322
  call void @llvm.dbg.declare(metadata %struct.passwd* %pwent, metadata !323, metadata !72), !dbg !334
  call void @llvm.dbg.declare(metadata %struct.passwd** %result, metadata !335, metadata !72), !dbg !337
  call void @llvm.dbg.declare(metadata i8** %nbuff, metadata !338, metadata !72), !dbg !339
  call void @llvm.dbg.declare(metadata i64* %nbuff_size, metadata !340, metadata !72), !dbg !341
  call void @llvm.dbg.declare(metadata i32* %r, metadata !342, metadata !72), !dbg !343
  %0 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !344
  %buff_size = getelementptr inbounds %struct.name_cache, %struct.name_cache* %0, i32 0, i32 2, !dbg !346
  %1 = load i64, i64* %buff_size, align 8, !dbg !346
  %cmp = icmp eq i64 %1, 0, !dbg !347
  br i1 %cmp, label %if.then, label %if.end, !dbg !348

if.then:                                          ; preds = %entry
  %2 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !349
  %buff_size1 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %2, i32 0, i32 2, !dbg !351
  store i64 256, i64* %buff_size1, align 8, !dbg !352
  %3 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !353
  %buff_size2 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %3, i32 0, i32 2, !dbg !354
  %4 = load i64, i64* %buff_size2, align 8, !dbg !354
  %call = call noalias i8* @malloc(i64 %4) #6, !dbg !355
  %5 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !356
  %buff = getelementptr inbounds %struct.name_cache, %struct.name_cache* %5, i32 0, i32 1, !dbg !357
  store i8* %call, i8** %buff, align 8, !dbg !358
  br label %if.end, !dbg !359

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !360
  %buff3 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %6, i32 0, i32 1, !dbg !362
  %7 = load i8*, i8** %buff3, align 8, !dbg !362
  %cmp4 = icmp eq i8* %7, null, !dbg !363
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !364

if.then5:                                         ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !365
  br label %return, !dbg !365

if.end6:                                          ; preds = %if.end
  br label %for.cond, !dbg !366

for.cond:                                         ; preds = %if.end21, %if.end6
  store %struct.passwd* %pwent, %struct.passwd** %result, align 8, !dbg !367
  %8 = load i32, i32* %id.addr, align 4, !dbg !371
  %9 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !372
  %buff7 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %9, i32 0, i32 1, !dbg !373
  %10 = load i8*, i8** %buff7, align 8, !dbg !373
  %11 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !374
  %buff_size8 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %11, i32 0, i32 2, !dbg !375
  %12 = load i64, i64* %buff_size8, align 8, !dbg !375
  %call9 = call i32 @getpwuid_r(i32 %8, %struct.passwd* %pwent, i8* %10, i64 %12, %struct.passwd** %result), !dbg !376
  store i32 %call9, i32* %r, align 4, !dbg !377
  %13 = load i32, i32* %r, align 4, !dbg !378
  %cmp10 = icmp eq i32 %13, 0, !dbg !380
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !381

if.then11:                                        ; preds = %for.cond
  br label %for.end, !dbg !382

if.end12:                                         ; preds = %for.cond
  %14 = load i32, i32* %r, align 4, !dbg !383
  %cmp13 = icmp ne i32 %14, 34, !dbg !385
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !386

if.then14:                                        ; preds = %if.end12
  br label %for.end, !dbg !387

if.end15:                                         ; preds = %if.end12
  %15 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !388
  %buff_size16 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %15, i32 0, i32 2, !dbg !389
  %16 = load i64, i64* %buff_size16, align 8, !dbg !389
  %mul = mul i64 %16, 2, !dbg !390
  store i64 %mul, i64* %nbuff_size, align 8, !dbg !391
  %17 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !392
  %buff17 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %17, i32 0, i32 1, !dbg !393
  %18 = load i8*, i8** %buff17, align 8, !dbg !393
  %19 = load i64, i64* %nbuff_size, align 8, !dbg !394
  %call18 = call i8* @realloc(i8* %18, i64 %19) #6, !dbg !395
  store i8* %call18, i8** %nbuff, align 8, !dbg !396
  %20 = load i8*, i8** %nbuff, align 8, !dbg !397
  %cmp19 = icmp eq i8* %20, null, !dbg !399
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !400

if.then20:                                        ; preds = %if.end15
  br label %for.end, !dbg !401

if.end21:                                         ; preds = %if.end15
  %21 = load i8*, i8** %nbuff, align 8, !dbg !402
  %22 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !403
  %buff22 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %22, i32 0, i32 1, !dbg !404
  store i8* %21, i8** %buff22, align 8, !dbg !405
  %23 = load i64, i64* %nbuff_size, align 8, !dbg !406
  %24 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !407
  %buff_size23 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %24, i32 0, i32 2, !dbg !408
  store i64 %23, i64* %buff_size23, align 8, !dbg !409
  br label %for.cond, !dbg !410

for.end:                                          ; preds = %if.then20, %if.then14, %if.then11
  %25 = load i32, i32* %r, align 4, !dbg !412
  %cmp24 = icmp ne i32 %25, 0, !dbg !414
  br i1 %cmp24, label %if.then25, label %if.end27, !dbg !415

if.then25:                                        ; preds = %for.end
  %26 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !416
  %archive = getelementptr inbounds %struct.name_cache, %struct.name_cache* %26, i32 0, i32 0, !dbg !418
  %27 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !418
  %call26 = call i32* @__errno_location() #1, !dbg !419
  %28 = load i32, i32* %call26, align 4, !dbg !419
  %29 = load i32, i32* %id.addr, align 4, !dbg !420
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %27, i32 %28, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.2, i32 0, i32 0), i32 %29), !dbg !421
  store i8* null, i8** %retval, align 8, !dbg !423
  br label %return, !dbg !423

if.end27:                                         ; preds = %for.end
  %30 = load %struct.passwd*, %struct.passwd** %result, align 8, !dbg !424
  %cmp28 = icmp eq %struct.passwd* %30, null, !dbg !426
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !427

if.then29:                                        ; preds = %if.end27
  store i8* null, i8** %retval, align 8, !dbg !428
  br label %return, !dbg !428

if.end30:                                         ; preds = %if.end27
  %31 = load %struct.passwd*, %struct.passwd** %result, align 8, !dbg !429
  %pw_name = getelementptr inbounds %struct.passwd, %struct.passwd* %31, i32 0, i32 0, !dbg !430
  %32 = load i8*, i8** %pw_name, align 8, !dbg !430
  %call31 = call noalias i8* @strdup(i8* %32) #6, !dbg !431
  store i8* %call31, i8** %retval, align 8, !dbg !432
  br label %return, !dbg !432

return:                                           ; preds = %if.end30, %if.then29, %if.then25, %if.then5
  %33 = load i8*, i8** %retval, align 8, !dbg !433
  ret i8* %33, !dbg !433
}

declare i32 @getpwuid_r(i32, %struct.passwd*, i8*, i64, %struct.passwd**) #3

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #2

; Function Attrs: nounwind uwtable
define internal i8* @lookup_gname_helper(%struct.name_cache* %cache, i32 %id) #0 !dbg !64 {
entry:
  %retval = alloca i8*, align 8
  %cache.addr = alloca %struct.name_cache*, align 8
  %id.addr = alloca i32, align 4
  %grent = alloca %struct.group, align 8
  %result = alloca %struct.group*, align 8
  %nbuff = alloca i8*, align 8
  %nbuff_size = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.name_cache* %cache, %struct.name_cache** %cache.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.name_cache** %cache.addr, metadata !434, metadata !72), !dbg !435
  store i32 %id, i32* %id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %id.addr, metadata !436, metadata !72), !dbg !437
  call void @llvm.dbg.declare(metadata %struct.group* %grent, metadata !438, metadata !72), !dbg !447
  call void @llvm.dbg.declare(metadata %struct.group** %result, metadata !448, metadata !72), !dbg !450
  call void @llvm.dbg.declare(metadata i8** %nbuff, metadata !451, metadata !72), !dbg !452
  call void @llvm.dbg.declare(metadata i64* %nbuff_size, metadata !453, metadata !72), !dbg !454
  call void @llvm.dbg.declare(metadata i32* %r, metadata !455, metadata !72), !dbg !456
  %0 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !457
  %buff_size = getelementptr inbounds %struct.name_cache, %struct.name_cache* %0, i32 0, i32 2, !dbg !459
  %1 = load i64, i64* %buff_size, align 8, !dbg !459
  %cmp = icmp eq i64 %1, 0, !dbg !460
  br i1 %cmp, label %if.then, label %if.end, !dbg !461

if.then:                                          ; preds = %entry
  %2 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !462
  %buff_size1 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %2, i32 0, i32 2, !dbg !464
  store i64 256, i64* %buff_size1, align 8, !dbg !465
  %3 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !466
  %buff_size2 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %3, i32 0, i32 2, !dbg !467
  %4 = load i64, i64* %buff_size2, align 8, !dbg !467
  %call = call noalias i8* @malloc(i64 %4) #6, !dbg !468
  %5 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !469
  %buff = getelementptr inbounds %struct.name_cache, %struct.name_cache* %5, i32 0, i32 1, !dbg !470
  store i8* %call, i8** %buff, align 8, !dbg !471
  br label %if.end, !dbg !472

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !473
  %buff3 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %6, i32 0, i32 1, !dbg !475
  %7 = load i8*, i8** %buff3, align 8, !dbg !475
  %cmp4 = icmp eq i8* %7, null, !dbg !476
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !477

if.then5:                                         ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !478
  br label %return, !dbg !478

if.end6:                                          ; preds = %if.end
  br label %for.cond, !dbg !479

for.cond:                                         ; preds = %if.end21, %if.end6
  store %struct.group* %grent, %struct.group** %result, align 8, !dbg !480
  %8 = load i32, i32* %id.addr, align 4, !dbg !484
  %9 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !485
  %buff7 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %9, i32 0, i32 1, !dbg !486
  %10 = load i8*, i8** %buff7, align 8, !dbg !486
  %11 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !487
  %buff_size8 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %11, i32 0, i32 2, !dbg !488
  %12 = load i64, i64* %buff_size8, align 8, !dbg !488
  %call9 = call i32 @getgrgid_r(i32 %8, %struct.group* %grent, i8* %10, i64 %12, %struct.group** %result), !dbg !489
  store i32 %call9, i32* %r, align 4, !dbg !490
  %13 = load i32, i32* %r, align 4, !dbg !491
  %cmp10 = icmp eq i32 %13, 0, !dbg !493
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !494

if.then11:                                        ; preds = %for.cond
  br label %for.end, !dbg !495

if.end12:                                         ; preds = %for.cond
  %14 = load i32, i32* %r, align 4, !dbg !496
  %cmp13 = icmp ne i32 %14, 34, !dbg !498
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !499

if.then14:                                        ; preds = %if.end12
  br label %for.end, !dbg !500

if.end15:                                         ; preds = %if.end12
  %15 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !501
  %buff_size16 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %15, i32 0, i32 2, !dbg !502
  %16 = load i64, i64* %buff_size16, align 8, !dbg !502
  %mul = mul i64 %16, 2, !dbg !503
  store i64 %mul, i64* %nbuff_size, align 8, !dbg !504
  %17 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !505
  %buff17 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %17, i32 0, i32 1, !dbg !506
  %18 = load i8*, i8** %buff17, align 8, !dbg !506
  %19 = load i64, i64* %nbuff_size, align 8, !dbg !507
  %call18 = call i8* @realloc(i8* %18, i64 %19) #6, !dbg !508
  store i8* %call18, i8** %nbuff, align 8, !dbg !509
  %20 = load i8*, i8** %nbuff, align 8, !dbg !510
  %cmp19 = icmp eq i8* %20, null, !dbg !512
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !513

if.then20:                                        ; preds = %if.end15
  br label %for.end, !dbg !514

if.end21:                                         ; preds = %if.end15
  %21 = load i8*, i8** %nbuff, align 8, !dbg !515
  %22 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !516
  %buff22 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %22, i32 0, i32 1, !dbg !517
  store i8* %21, i8** %buff22, align 8, !dbg !518
  %23 = load i64, i64* %nbuff_size, align 8, !dbg !519
  %24 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !520
  %buff_size23 = getelementptr inbounds %struct.name_cache, %struct.name_cache* %24, i32 0, i32 2, !dbg !521
  store i64 %23, i64* %buff_size23, align 8, !dbg !522
  br label %for.cond, !dbg !523

for.end:                                          ; preds = %if.then20, %if.then14, %if.then11
  %25 = load i32, i32* %r, align 4, !dbg !525
  %cmp24 = icmp ne i32 %25, 0, !dbg !527
  br i1 %cmp24, label %if.then25, label %if.end27, !dbg !528

if.then25:                                        ; preds = %for.end
  %26 = load %struct.name_cache*, %struct.name_cache** %cache.addr, align 8, !dbg !529
  %archive = getelementptr inbounds %struct.name_cache, %struct.name_cache* %26, i32 0, i32 0, !dbg !531
  %27 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !531
  %call26 = call i32* @__errno_location() #1, !dbg !532
  %28 = load i32, i32* %call26, align 4, !dbg !532
  %29 = load i32, i32* %id.addr, align 4, !dbg !533
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %27, i32 %28, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.3, i32 0, i32 0), i32 %29), !dbg !534
  store i8* null, i8** %retval, align 8, !dbg !536
  br label %return, !dbg !536

if.end27:                                         ; preds = %for.end
  %30 = load %struct.group*, %struct.group** %result, align 8, !dbg !537
  %cmp28 = icmp eq %struct.group* %30, null, !dbg !539
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !540

if.then29:                                        ; preds = %if.end27
  store i8* null, i8** %retval, align 8, !dbg !541
  br label %return, !dbg !541

if.end30:                                         ; preds = %if.end27
  %31 = load %struct.group*, %struct.group** %result, align 8, !dbg !542
  %gr_name = getelementptr inbounds %struct.group, %struct.group* %31, i32 0, i32 0, !dbg !543
  %32 = load i8*, i8** %gr_name, align 8, !dbg !543
  %call31 = call noalias i8* @strdup(i8* %32) #6, !dbg !544
  store i8* %call31, i8** %retval, align 8, !dbg !545
  br label %return, !dbg !545

return:                                           ; preds = %if.end30, %if.then29, %if.then25, %if.then5
  %33 = load i8*, i8** %retval, align 8, !dbg !546
  ret i8* %33, !dbg !546
}

declare i32 @getgrgid_r(i32, %struct.group*, i8*, i64, %struct.group**) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!68, !69}
!llvm.ident = !{!70}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !44, globals: !65)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_set_standard_lookup.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !38, !28, !40, !20, !42}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "name_cache", file: !1, line: 62, size: 16576, align: 64, elements: !7)
!7 = !{!8, !12, !15, !19, !21, !22, !23}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !6, file: !1, line: 63, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !11, line: 179, flags: DIFlagFwdDecl)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!12 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !6, file: !1, line: 64, baseType: !13, size: 64, align: 64, offset: 64)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!14 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "buff_size", scope: !6, file: !1, line: 65, baseType: !16, size: 64, align: 64, offset: 128)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !17, line: 62, baseType: !18)
!17 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "probes", scope: !6, file: !1, line: 66, baseType: !20, size: 32, align: 32, offset: 192)
!20 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "hits", scope: !6, file: !1, line: 67, baseType: !20, size: 32, align: 32, offset: 224)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !6, file: !1, line: 68, baseType: !16, size: 64, align: 64, offset: 256)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !6, file: !1, line: 72, baseType: !24, size: 16256, align: 64, offset: 320)
!24 = !DICompositeType(tag: DW_TAG_array_type, baseType: !25, size: 16256, align: 64, elements: !36)
!25 = !DICompositeType(tag: DW_TAG_structure_type, scope: !6, file: !1, line: 69, size: 128, align: 64, elements: !26)
!26 = !{!27, !33}
!27 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !25, file: !1, line: 70, baseType: !28, size: 32, align: 32)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "id_t", file: !29, line: 104, baseType: !30)
!29 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "__id_t", file: !31, line: 138, baseType: !32)
!31 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!32 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !25, file: !1, line: 71, baseType: !34, size: 64, align: 64, offset: 64)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !14)
!36 = !{!37}
!37 = !DISubrange(count: 127)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !39, line: 122, baseType: !18)
!39 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !29, line: 80, baseType: !41)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !31, line: 125, baseType: !32)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !29, line: 65, baseType: !43)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !31, line: 126, baseType: !32)
!44 = !{!45, !48, !51, !56, !62, !63, !64}
!45 = distinct !DISubprogram(name: "archive_read_disk_set_standard_lookup", scope: !1, file: !1, line: 95, type: !46, isLocal: false, isDefinition: true, scopeLine: 96, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!46 = !DISubroutineType(types: !47)
!47 = !{!20, !9}
!48 = distinct !DISubprogram(name: "cleanup", scope: !1, file: !1, line: 122, type: !49, isLocal: true, isDefinition: true, scopeLine: 123, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!49 = !DISubroutineType(types: !50)
!50 = !{null, !4}
!51 = distinct !DISubprogram(name: "lookup_uname", scope: !1, file: !1, line: 178, type: !52, isLocal: true, isDefinition: true, scopeLine: 179, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!52 = !DISubroutineType(types: !53)
!53 = !{!34, !4, !54}
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !39, line: 40, baseType: !55)
!55 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!56 = distinct !DISubprogram(name: "lookup_name", scope: !1, file: !1, line: 142, type: !57, isLocal: true, isDefinition: true, scopeLine: 144, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!57 = !DISubroutineType(types: !58)
!58 = !{!34, !5, !59, !28}
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!34, !5, !28}
!62 = distinct !DISubprogram(name: "lookup_uname_helper", scope: !1, file: !1, line: 187, type: !60, isLocal: true, isDefinition: true, scopeLine: 188, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!63 = distinct !DISubprogram(name: "lookup_gname", scope: !1, file: !1, line: 247, type: !52, isLocal: true, isDefinition: true, scopeLine: 248, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!64 = distinct !DISubprogram(name: "lookup_gname_helper", scope: !1, file: !1, line: 256, type: !60, isLocal: true, isDefinition: true, scopeLine: 257, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!65 = !{!66}
!66 = !DIGlobalVariable(name: "NO_NAME", scope: !0, file: !1, line: 60, type: !67, isLocal: true, isDefinition: true, variable: i8** @NO_NAME)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !34)
!68 = !{i32 2, !"Dwarf Version", i32 4}
!69 = !{i32 2, !"Debug Info Version", i32 3}
!70 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!71 = !DILocalVariable(name: "a", arg: 1, scope: !45, file: !1, line: 95, type: !9)
!72 = !DIExpression()
!73 = !DILocation(line: 95, column: 55, scope: !45)
!74 = !DILocalVariable(name: "ucache", scope: !45, file: !1, line: 97, type: !5)
!75 = !DILocation(line: 97, column: 21, scope: !45)
!76 = !DILocation(line: 97, column: 30, scope: !45)
!77 = !DILocalVariable(name: "gcache", scope: !45, file: !1, line: 98, type: !5)
!78 = !DILocation(line: 98, column: 21, scope: !45)
!79 = !DILocation(line: 98, column: 30, scope: !45)
!80 = !DILocation(line: 100, column: 6, scope: !81)
!81 = distinct !DILexicalBlock(scope: !45, file: !1, line: 100, column: 6)
!82 = !DILocation(line: 100, column: 13, scope: !81)
!83 = !DILocation(line: 100, column: 21, scope: !81)
!84 = !DILocation(line: 100, column: 24, scope: !85)
!85 = !DILexicalBlockFile(scope: !81, file: !1, discriminator: 1)
!86 = !DILocation(line: 100, column: 31, scope: !85)
!87 = !DILocation(line: 100, column: 6, scope: !85)
!88 = !DILocation(line: 101, column: 21, scope: !89)
!89 = distinct !DILexicalBlock(scope: !81, file: !1, line: 100, column: 40)
!90 = !DILocation(line: 101, column: 3, scope: !89)
!91 = !DILocation(line: 103, column: 8, scope: !89)
!92 = !DILocation(line: 103, column: 3, scope: !89)
!93 = !DILocation(line: 104, column: 8, scope: !89)
!94 = !DILocation(line: 104, column: 3, scope: !89)
!95 = !DILocation(line: 105, column: 3, scope: !89)
!96 = !DILocation(line: 108, column: 9, scope: !45)
!97 = !DILocation(line: 108, column: 2, scope: !45)
!98 = !DILocation(line: 109, column: 20, scope: !45)
!99 = !DILocation(line: 109, column: 2, scope: !45)
!100 = !DILocation(line: 109, column: 10, scope: !45)
!101 = !DILocation(line: 109, column: 18, scope: !45)
!102 = !DILocation(line: 110, column: 2, scope: !45)
!103 = !DILocation(line: 110, column: 10, scope: !45)
!104 = !DILocation(line: 110, column: 15, scope: !45)
!105 = !DILocation(line: 111, column: 9, scope: !45)
!106 = !DILocation(line: 111, column: 2, scope: !45)
!107 = !DILocation(line: 112, column: 20, scope: !45)
!108 = !DILocation(line: 112, column: 2, scope: !45)
!109 = !DILocation(line: 112, column: 10, scope: !45)
!110 = !DILocation(line: 112, column: 18, scope: !45)
!111 = !DILocation(line: 113, column: 2, scope: !45)
!112 = !DILocation(line: 113, column: 10, scope: !45)
!113 = !DILocation(line: 113, column: 15, scope: !45)
!114 = !DILocation(line: 115, column: 37, scope: !45)
!115 = !DILocation(line: 115, column: 40, scope: !45)
!116 = !DILocation(line: 115, column: 2, scope: !45)
!117 = !DILocation(line: 116, column: 37, scope: !45)
!118 = !DILocation(line: 116, column: 40, scope: !45)
!119 = !DILocation(line: 116, column: 2, scope: !45)
!120 = !DILocation(line: 118, column: 2, scope: !45)
!121 = !DILocation(line: 119, column: 1, scope: !45)
!122 = !DILocalVariable(name: "data", arg: 1, scope: !63, file: !1, line: 247, type: !4)
!123 = !DILocation(line: 247, column: 20, scope: !63)
!124 = !DILocalVariable(name: "gid", arg: 2, scope: !63, file: !1, line: 247, type: !54)
!125 = !DILocation(line: 247, column: 34, scope: !63)
!126 = !DILocalVariable(name: "gname_cache", scope: !63, file: !1, line: 249, type: !5)
!127 = !DILocation(line: 249, column: 21, scope: !63)
!128 = !DILocation(line: 249, column: 56, scope: !63)
!129 = !DILocation(line: 249, column: 35, scope: !63)
!130 = !DILocation(line: 250, column: 22, scope: !63)
!131 = !DILocation(line: 251, column: 35, scope: !63)
!132 = !DILocation(line: 251, column: 29, scope: !63)
!133 = !DILocation(line: 250, column: 10, scope: !63)
!134 = !DILocation(line: 250, column: 2, scope: !63)
!135 = !DILocalVariable(name: "data", arg: 1, scope: !48, file: !1, line: 122, type: !4)
!136 = !DILocation(line: 122, column: 15, scope: !48)
!137 = !DILocalVariable(name: "cache", scope: !48, file: !1, line: 124, type: !5)
!138 = !DILocation(line: 124, column: 21, scope: !48)
!139 = !DILocation(line: 124, column: 50, scope: !48)
!140 = !DILocation(line: 124, column: 29, scope: !48)
!141 = !DILocalVariable(name: "i", scope: !48, file: !1, line: 125, type: !16)
!142 = !DILocation(line: 125, column: 9, scope: !48)
!143 = !DILocation(line: 127, column: 6, scope: !144)
!144 = distinct !DILexicalBlock(scope: !48, file: !1, line: 127, column: 6)
!145 = !DILocation(line: 127, column: 12, scope: !144)
!146 = !DILocation(line: 127, column: 6, scope: !48)
!147 = !DILocation(line: 128, column: 10, scope: !148)
!148 = distinct !DILexicalBlock(scope: !149, file: !1, line: 128, column: 3)
!149 = distinct !DILexicalBlock(scope: !144, file: !1, line: 127, column: 21)
!150 = !DILocation(line: 128, column: 8, scope: !148)
!151 = !DILocation(line: 128, column: 15, scope: !152)
!152 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 1)
!153 = distinct !DILexicalBlock(scope: !148, file: !1, line: 128, column: 3)
!154 = !DILocation(line: 128, column: 19, scope: !152)
!155 = !DILocation(line: 128, column: 26, scope: !152)
!156 = !DILocation(line: 128, column: 17, scope: !152)
!157 = !DILocation(line: 128, column: 3, scope: !152)
!158 = !DILocation(line: 129, column: 21, scope: !159)
!159 = distinct !DILexicalBlock(scope: !160, file: !1, line: 129, column: 8)
!160 = distinct !DILexicalBlock(scope: !153, file: !1, line: 128, column: 37)
!161 = !DILocation(line: 129, column: 8, scope: !159)
!162 = !DILocation(line: 129, column: 15, scope: !159)
!163 = !DILocation(line: 129, column: 24, scope: !159)
!164 = !DILocation(line: 129, column: 29, scope: !159)
!165 = !DILocation(line: 129, column: 37, scope: !159)
!166 = !DILocation(line: 130, column: 21, scope: !159)
!167 = !DILocation(line: 130, column: 8, scope: !159)
!168 = !DILocation(line: 130, column: 15, scope: !159)
!169 = !DILocation(line: 130, column: 24, scope: !159)
!170 = !DILocation(line: 130, column: 32, scope: !159)
!171 = !DILocation(line: 130, column: 29, scope: !159)
!172 = !DILocation(line: 129, column: 8, scope: !173)
!173 = !DILexicalBlockFile(scope: !160, file: !1, discriminator: 1)
!174 = !DILocation(line: 131, column: 42, scope: !159)
!175 = !DILocation(line: 131, column: 29, scope: !159)
!176 = !DILocation(line: 131, column: 36, scope: !159)
!177 = !DILocation(line: 131, column: 45, scope: !159)
!178 = !DILocation(line: 131, column: 18, scope: !159)
!179 = !DILocation(line: 131, column: 10, scope: !159)
!180 = !DILocation(line: 131, column: 5, scope: !159)
!181 = !DILocation(line: 132, column: 3, scope: !160)
!182 = !DILocation(line: 128, column: 33, scope: !183)
!183 = !DILexicalBlockFile(scope: !153, file: !1, discriminator: 2)
!184 = !DILocation(line: 128, column: 3, scope: !183)
!185 = !DILocation(line: 133, column: 8, scope: !149)
!186 = !DILocation(line: 133, column: 15, scope: !149)
!187 = !DILocation(line: 133, column: 3, scope: !149)
!188 = !DILocation(line: 134, column: 8, scope: !149)
!189 = !DILocation(line: 134, column: 3, scope: !149)
!190 = !DILocation(line: 135, column: 2, scope: !149)
!191 = !DILocation(line: 136, column: 1, scope: !48)
!192 = !DILocalVariable(name: "data", arg: 1, scope: !51, file: !1, line: 178, type: !4)
!193 = !DILocation(line: 178, column: 20, scope: !51)
!194 = !DILocalVariable(name: "uid", arg: 2, scope: !51, file: !1, line: 178, type: !54)
!195 = !DILocation(line: 178, column: 34, scope: !51)
!196 = !DILocalVariable(name: "uname_cache", scope: !51, file: !1, line: 180, type: !5)
!197 = !DILocation(line: 180, column: 21, scope: !51)
!198 = !DILocation(line: 180, column: 56, scope: !51)
!199 = !DILocation(line: 180, column: 35, scope: !51)
!200 = !DILocation(line: 181, column: 22, scope: !51)
!201 = !DILocation(line: 182, column: 35, scope: !51)
!202 = !DILocation(line: 182, column: 29, scope: !51)
!203 = !DILocation(line: 181, column: 10, scope: !51)
!204 = !DILocation(line: 181, column: 2, scope: !51)
!205 = !DILocalVariable(name: "cache", arg: 1, scope: !56, file: !1, line: 142, type: !5)
!206 = !DILocation(line: 142, column: 32, scope: !56)
!207 = !DILocalVariable(name: "lookup_fn", arg: 2, scope: !56, file: !1, line: 143, type: !59)
!208 = !DILocation(line: 143, column: 20, scope: !56)
!209 = !DILocalVariable(name: "id", arg: 3, scope: !56, file: !1, line: 143, type: !28)
!210 = !DILocation(line: 143, column: 64, scope: !56)
!211 = !DILocalVariable(name: "name", scope: !56, file: !1, line: 145, type: !34)
!212 = !DILocation(line: 145, column: 14, scope: !56)
!213 = !DILocalVariable(name: "slot", scope: !56, file: !1, line: 146, type: !20)
!214 = !DILocation(line: 146, column: 6, scope: !56)
!215 = !DILocation(line: 149, column: 2, scope: !56)
!216 = !DILocation(line: 149, column: 9, scope: !56)
!217 = !DILocation(line: 149, column: 15, scope: !56)
!218 = !DILocation(line: 151, column: 9, scope: !56)
!219 = !DILocation(line: 151, column: 14, scope: !56)
!220 = !DILocation(line: 151, column: 21, scope: !56)
!221 = !DILocation(line: 151, column: 12, scope: !56)
!222 = !DILocation(line: 151, column: 7, scope: !56)
!223 = !DILocation(line: 152, column: 19, scope: !224)
!224 = distinct !DILexicalBlock(scope: !56, file: !1, line: 152, column: 6)
!225 = !DILocation(line: 152, column: 6, scope: !224)
!226 = !DILocation(line: 152, column: 13, scope: !224)
!227 = !DILocation(line: 152, column: 25, scope: !224)
!228 = !DILocation(line: 152, column: 30, scope: !224)
!229 = !DILocation(line: 152, column: 6, scope: !56)
!230 = !DILocation(line: 153, column: 20, scope: !231)
!231 = distinct !DILexicalBlock(scope: !232, file: !1, line: 153, column: 7)
!232 = distinct !DILexicalBlock(scope: !224, file: !1, line: 152, column: 39)
!233 = !DILocation(line: 153, column: 7, scope: !231)
!234 = !DILocation(line: 153, column: 14, scope: !231)
!235 = !DILocation(line: 153, column: 26, scope: !231)
!236 = !DILocation(line: 153, column: 32, scope: !231)
!237 = !DILocation(line: 153, column: 29, scope: !231)
!238 = !DILocation(line: 153, column: 7, scope: !232)
!239 = !DILocation(line: 154, column: 4, scope: !240)
!240 = distinct !DILexicalBlock(scope: !231, file: !1, line: 153, column: 36)
!241 = !DILocation(line: 154, column: 11, scope: !240)
!242 = !DILocation(line: 154, column: 15, scope: !240)
!243 = !DILocation(line: 155, column: 21, scope: !244)
!244 = distinct !DILexicalBlock(scope: !240, file: !1, line: 155, column: 8)
!245 = !DILocation(line: 155, column: 8, scope: !244)
!246 = !DILocation(line: 155, column: 15, scope: !244)
!247 = !DILocation(line: 155, column: 27, scope: !244)
!248 = !DILocation(line: 155, column: 35, scope: !244)
!249 = !DILocation(line: 155, column: 32, scope: !244)
!250 = !DILocation(line: 155, column: 8, scope: !240)
!251 = !DILocation(line: 156, column: 5, scope: !244)
!252 = !DILocation(line: 157, column: 25, scope: !240)
!253 = !DILocation(line: 157, column: 12, scope: !240)
!254 = !DILocation(line: 157, column: 19, scope: !240)
!255 = !DILocation(line: 157, column: 31, scope: !240)
!256 = !DILocation(line: 157, column: 4, scope: !240)
!257 = !DILocation(line: 159, column: 20, scope: !258)
!258 = distinct !DILexicalBlock(scope: !232, file: !1, line: 159, column: 7)
!259 = !DILocation(line: 159, column: 7, scope: !258)
!260 = !DILocation(line: 159, column: 14, scope: !258)
!261 = !DILocation(line: 159, column: 26, scope: !258)
!262 = !DILocation(line: 159, column: 34, scope: !258)
!263 = !DILocation(line: 159, column: 31, scope: !258)
!264 = !DILocation(line: 159, column: 7, scope: !232)
!265 = !DILocation(line: 160, column: 41, scope: !258)
!266 = !DILocation(line: 160, column: 28, scope: !258)
!267 = !DILocation(line: 160, column: 35, scope: !258)
!268 = !DILocation(line: 160, column: 47, scope: !258)
!269 = !DILocation(line: 160, column: 17, scope: !258)
!270 = !DILocation(line: 160, column: 9, scope: !258)
!271 = !DILocation(line: 160, column: 4, scope: !258)
!272 = !DILocation(line: 161, column: 16, scope: !232)
!273 = !DILocation(line: 161, column: 3, scope: !232)
!274 = !DILocation(line: 161, column: 10, scope: !232)
!275 = !DILocation(line: 161, column: 22, scope: !232)
!276 = !DILocation(line: 161, column: 27, scope: !232)
!277 = !DILocation(line: 162, column: 2, scope: !232)
!278 = !DILocation(line: 164, column: 10, scope: !56)
!279 = !DILocation(line: 164, column: 21, scope: !56)
!280 = !DILocation(line: 164, column: 28, scope: !56)
!281 = !DILocation(line: 164, column: 9, scope: !56)
!282 = !DILocation(line: 164, column: 7, scope: !56)
!283 = !DILocation(line: 165, column: 6, scope: !284)
!284 = distinct !DILexicalBlock(scope: !56, file: !1, line: 165, column: 6)
!285 = !DILocation(line: 165, column: 11, scope: !284)
!286 = !DILocation(line: 165, column: 6, scope: !56)
!287 = !DILocation(line: 167, column: 29, scope: !288)
!288 = distinct !DILexicalBlock(scope: !284, file: !1, line: 165, column: 20)
!289 = !DILocation(line: 167, column: 16, scope: !288)
!290 = !DILocation(line: 167, column: 3, scope: !288)
!291 = !DILocation(line: 167, column: 10, scope: !288)
!292 = !DILocation(line: 167, column: 22, scope: !288)
!293 = !DILocation(line: 167, column: 27, scope: !288)
!294 = !DILocation(line: 168, column: 27, scope: !288)
!295 = !DILocation(line: 168, column: 16, scope: !288)
!296 = !DILocation(line: 168, column: 3, scope: !288)
!297 = !DILocation(line: 168, column: 10, scope: !288)
!298 = !DILocation(line: 168, column: 22, scope: !288)
!299 = !DILocation(line: 168, column: 25, scope: !288)
!300 = !DILocation(line: 169, column: 3, scope: !288)
!301 = !DILocation(line: 172, column: 28, scope: !56)
!302 = !DILocation(line: 172, column: 15, scope: !56)
!303 = !DILocation(line: 172, column: 2, scope: !56)
!304 = !DILocation(line: 172, column: 9, scope: !56)
!305 = !DILocation(line: 172, column: 21, scope: !56)
!306 = !DILocation(line: 172, column: 26, scope: !56)
!307 = !DILocation(line: 173, column: 26, scope: !56)
!308 = !DILocation(line: 173, column: 15, scope: !56)
!309 = !DILocation(line: 173, column: 2, scope: !56)
!310 = !DILocation(line: 173, column: 9, scope: !56)
!311 = !DILocation(line: 173, column: 21, scope: !56)
!312 = !DILocation(line: 173, column: 24, scope: !56)
!313 = !DILocation(line: 174, column: 23, scope: !56)
!314 = !DILocation(line: 174, column: 10, scope: !56)
!315 = !DILocation(line: 174, column: 17, scope: !56)
!316 = !DILocation(line: 174, column: 29, scope: !56)
!317 = !DILocation(line: 174, column: 2, scope: !56)
!318 = !DILocation(line: 175, column: 1, scope: !56)
!319 = !DILocalVariable(name: "cache", arg: 1, scope: !62, file: !1, line: 187, type: !5)
!320 = !DILocation(line: 187, column: 40, scope: !62)
!321 = !DILocalVariable(name: "id", arg: 2, scope: !62, file: !1, line: 187, type: !28)
!322 = !DILocation(line: 187, column: 52, scope: !62)
!323 = !DILocalVariable(name: "pwent", scope: !62, file: !1, line: 189, type: !324)
!324 = !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !325, line: 49, size: 384, align: 64, elements: !326)
!325 = !DIFile(filename: "/usr/include/pwd.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!326 = !{!327, !328, !329, !330, !331, !332, !333}
!327 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !324, file: !325, line: 51, baseType: !13, size: 64, align: 64)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !324, file: !325, line: 52, baseType: !13, size: 64, align: 64, offset: 64)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !324, file: !325, line: 53, baseType: !41, size: 32, align: 32, offset: 128)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !324, file: !325, line: 54, baseType: !43, size: 32, align: 32, offset: 160)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !324, file: !325, line: 55, baseType: !13, size: 64, align: 64, offset: 192)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !324, file: !325, line: 56, baseType: !13, size: 64, align: 64, offset: 256)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !324, file: !325, line: 57, baseType: !13, size: 64, align: 64, offset: 320)
!334 = !DILocation(line: 189, column: 16, scope: !62)
!335 = !DILocalVariable(name: "result", scope: !62, file: !1, line: 189, type: !336)
!336 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !324, size: 64, align: 64)
!337 = !DILocation(line: 189, column: 24, scope: !62)
!338 = !DILocalVariable(name: "nbuff", scope: !62, file: !1, line: 190, type: !13)
!339 = !DILocation(line: 190, column: 9, scope: !62)
!340 = !DILocalVariable(name: "nbuff_size", scope: !62, file: !1, line: 191, type: !16)
!341 = !DILocation(line: 191, column: 9, scope: !62)
!342 = !DILocalVariable(name: "r", scope: !62, file: !1, line: 192, type: !20)
!343 = !DILocation(line: 192, column: 6, scope: !62)
!344 = !DILocation(line: 194, column: 6, scope: !345)
!345 = distinct !DILexicalBlock(scope: !62, file: !1, line: 194, column: 6)
!346 = !DILocation(line: 194, column: 13, scope: !345)
!347 = !DILocation(line: 194, column: 23, scope: !345)
!348 = !DILocation(line: 194, column: 6, scope: !62)
!349 = !DILocation(line: 195, column: 3, scope: !350)
!350 = distinct !DILexicalBlock(scope: !345, file: !1, line: 194, column: 29)
!351 = !DILocation(line: 195, column: 10, scope: !350)
!352 = !DILocation(line: 195, column: 20, scope: !350)
!353 = !DILocation(line: 196, column: 24, scope: !350)
!354 = !DILocation(line: 196, column: 31, scope: !350)
!355 = !DILocation(line: 196, column: 17, scope: !350)
!356 = !DILocation(line: 196, column: 3, scope: !350)
!357 = !DILocation(line: 196, column: 10, scope: !350)
!358 = !DILocation(line: 196, column: 15, scope: !350)
!359 = !DILocation(line: 197, column: 2, scope: !350)
!360 = !DILocation(line: 198, column: 6, scope: !361)
!361 = distinct !DILexicalBlock(scope: !62, file: !1, line: 198, column: 6)
!362 = !DILocation(line: 198, column: 13, scope: !361)
!363 = !DILocation(line: 198, column: 18, scope: !361)
!364 = !DILocation(line: 198, column: 6, scope: !62)
!365 = !DILocation(line: 199, column: 3, scope: !361)
!366 = !DILocation(line: 200, column: 2, scope: !62)
!367 = !DILocation(line: 201, column: 10, scope: !368)
!368 = distinct !DILexicalBlock(scope: !369, file: !1, line: 200, column: 11)
!369 = distinct !DILexicalBlock(scope: !370, file: !1, line: 200, column: 2)
!370 = distinct !DILexicalBlock(scope: !62, file: !1, line: 200, column: 2)
!371 = !DILocation(line: 202, column: 25, scope: !368)
!372 = !DILocation(line: 203, column: 11, scope: !368)
!373 = !DILocation(line: 203, column: 18, scope: !368)
!374 = !DILocation(line: 203, column: 24, scope: !368)
!375 = !DILocation(line: 203, column: 31, scope: !368)
!376 = !DILocation(line: 202, column: 7, scope: !368)
!377 = !DILocation(line: 202, column: 5, scope: !368)
!378 = !DILocation(line: 204, column: 7, scope: !379)
!379 = distinct !DILexicalBlock(scope: !368, file: !1, line: 204, column: 7)
!380 = !DILocation(line: 204, column: 9, scope: !379)
!381 = !DILocation(line: 204, column: 7, scope: !368)
!382 = !DILocation(line: 205, column: 4, scope: !379)
!383 = !DILocation(line: 206, column: 7, scope: !384)
!384 = distinct !DILexicalBlock(scope: !368, file: !1, line: 206, column: 7)
!385 = !DILocation(line: 206, column: 9, scope: !384)
!386 = !DILocation(line: 206, column: 7, scope: !368)
!387 = !DILocation(line: 207, column: 4, scope: !384)
!388 = !DILocation(line: 213, column: 16, scope: !368)
!389 = !DILocation(line: 213, column: 23, scope: !368)
!390 = !DILocation(line: 213, column: 33, scope: !368)
!391 = !DILocation(line: 213, column: 14, scope: !368)
!392 = !DILocation(line: 214, column: 19, scope: !368)
!393 = !DILocation(line: 214, column: 26, scope: !368)
!394 = !DILocation(line: 214, column: 32, scope: !368)
!395 = !DILocation(line: 214, column: 11, scope: !368)
!396 = !DILocation(line: 214, column: 9, scope: !368)
!397 = !DILocation(line: 215, column: 7, scope: !398)
!398 = distinct !DILexicalBlock(scope: !368, file: !1, line: 215, column: 7)
!399 = !DILocation(line: 215, column: 13, scope: !398)
!400 = !DILocation(line: 215, column: 7, scope: !368)
!401 = !DILocation(line: 216, column: 4, scope: !398)
!402 = !DILocation(line: 217, column: 17, scope: !368)
!403 = !DILocation(line: 217, column: 3, scope: !368)
!404 = !DILocation(line: 217, column: 10, scope: !368)
!405 = !DILocation(line: 217, column: 15, scope: !368)
!406 = !DILocation(line: 218, column: 22, scope: !368)
!407 = !DILocation(line: 218, column: 3, scope: !368)
!408 = !DILocation(line: 218, column: 10, scope: !368)
!409 = !DILocation(line: 218, column: 20, scope: !368)
!410 = !DILocation(line: 200, column: 2, scope: !411)
!411 = !DILexicalBlockFile(scope: !369, file: !1, discriminator: 1)
!412 = !DILocation(line: 220, column: 6, scope: !413)
!413 = distinct !DILexicalBlock(scope: !62, file: !1, line: 220, column: 6)
!414 = !DILocation(line: 220, column: 8, scope: !413)
!415 = !DILocation(line: 220, column: 6, scope: !62)
!416 = !DILocation(line: 221, column: 21, scope: !417)
!417 = distinct !DILexicalBlock(scope: !413, file: !1, line: 220, column: 14)
!418 = !DILocation(line: 221, column: 28, scope: !417)
!419 = !DILocation(line: 221, column: 37, scope: !417)
!420 = !DILocation(line: 222, column: 43, scope: !417)
!421 = !DILocation(line: 221, column: 3, scope: !422)
!422 = !DILexicalBlockFile(scope: !417, file: !1, discriminator: 1)
!423 = !DILocation(line: 223, column: 3, scope: !417)
!424 = !DILocation(line: 225, column: 6, scope: !425)
!425 = distinct !DILexicalBlock(scope: !62, file: !1, line: 225, column: 6)
!426 = !DILocation(line: 225, column: 13, scope: !425)
!427 = !DILocation(line: 225, column: 6, scope: !62)
!428 = !DILocation(line: 226, column: 3, scope: !425)
!429 = !DILocation(line: 228, column: 16, scope: !62)
!430 = !DILocation(line: 228, column: 24, scope: !62)
!431 = !DILocation(line: 228, column: 9, scope: !62)
!432 = !DILocation(line: 228, column: 2, scope: !62)
!433 = !DILocation(line: 229, column: 1, scope: !62)
!434 = !DILocalVariable(name: "cache", arg: 1, scope: !64, file: !1, line: 256, type: !5)
!435 = !DILocation(line: 256, column: 40, scope: !64)
!436 = !DILocalVariable(name: "id", arg: 2, scope: !64, file: !1, line: 256, type: !28)
!437 = !DILocation(line: 256, column: 52, scope: !64)
!438 = !DILocalVariable(name: "grent", scope: !64, file: !1, line: 258, type: !439)
!439 = !DICompositeType(tag: DW_TAG_structure_type, name: "group", file: !440, line: 42, size: 256, align: 64, elements: !441)
!440 = !DIFile(filename: "/usr/include/grp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!441 = !{!442, !443, !444, !445}
!442 = !DIDerivedType(tag: DW_TAG_member, name: "gr_name", scope: !439, file: !440, line: 44, baseType: !13, size: 64, align: 64)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "gr_passwd", scope: !439, file: !440, line: 45, baseType: !13, size: 64, align: 64, offset: 64)
!444 = !DIDerivedType(tag: DW_TAG_member, name: "gr_gid", scope: !439, file: !440, line: 46, baseType: !43, size: 32, align: 32, offset: 128)
!445 = !DIDerivedType(tag: DW_TAG_member, name: "gr_mem", scope: !439, file: !440, line: 47, baseType: !446, size: 64, align: 64, offset: 192)
!446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!447 = !DILocation(line: 258, column: 15, scope: !64)
!448 = !DILocalVariable(name: "result", scope: !64, file: !1, line: 258, type: !449)
!449 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !439, size: 64, align: 64)
!450 = !DILocation(line: 258, column: 23, scope: !64)
!451 = !DILocalVariable(name: "nbuff", scope: !64, file: !1, line: 259, type: !13)
!452 = !DILocation(line: 259, column: 9, scope: !64)
!453 = !DILocalVariable(name: "nbuff_size", scope: !64, file: !1, line: 260, type: !16)
!454 = !DILocation(line: 260, column: 9, scope: !64)
!455 = !DILocalVariable(name: "r", scope: !64, file: !1, line: 261, type: !20)
!456 = !DILocation(line: 261, column: 6, scope: !64)
!457 = !DILocation(line: 263, column: 6, scope: !458)
!458 = distinct !DILexicalBlock(scope: !64, file: !1, line: 263, column: 6)
!459 = !DILocation(line: 263, column: 13, scope: !458)
!460 = !DILocation(line: 263, column: 23, scope: !458)
!461 = !DILocation(line: 263, column: 6, scope: !64)
!462 = !DILocation(line: 264, column: 3, scope: !463)
!463 = distinct !DILexicalBlock(scope: !458, file: !1, line: 263, column: 29)
!464 = !DILocation(line: 264, column: 10, scope: !463)
!465 = !DILocation(line: 264, column: 20, scope: !463)
!466 = !DILocation(line: 265, column: 24, scope: !463)
!467 = !DILocation(line: 265, column: 31, scope: !463)
!468 = !DILocation(line: 265, column: 17, scope: !463)
!469 = !DILocation(line: 265, column: 3, scope: !463)
!470 = !DILocation(line: 265, column: 10, scope: !463)
!471 = !DILocation(line: 265, column: 15, scope: !463)
!472 = !DILocation(line: 266, column: 2, scope: !463)
!473 = !DILocation(line: 267, column: 6, scope: !474)
!474 = distinct !DILexicalBlock(scope: !64, file: !1, line: 267, column: 6)
!475 = !DILocation(line: 267, column: 13, scope: !474)
!476 = !DILocation(line: 267, column: 18, scope: !474)
!477 = !DILocation(line: 267, column: 6, scope: !64)
!478 = !DILocation(line: 268, column: 3, scope: !474)
!479 = !DILocation(line: 269, column: 2, scope: !64)
!480 = !DILocation(line: 270, column: 10, scope: !481)
!481 = distinct !DILexicalBlock(scope: !482, file: !1, line: 269, column: 11)
!482 = distinct !DILexicalBlock(scope: !483, file: !1, line: 269, column: 2)
!483 = distinct !DILexicalBlock(scope: !64, file: !1, line: 269, column: 2)
!484 = !DILocation(line: 271, column: 25, scope: !481)
!485 = !DILocation(line: 272, column: 11, scope: !481)
!486 = !DILocation(line: 272, column: 18, scope: !481)
!487 = !DILocation(line: 272, column: 24, scope: !481)
!488 = !DILocation(line: 272, column: 31, scope: !481)
!489 = !DILocation(line: 271, column: 7, scope: !481)
!490 = !DILocation(line: 271, column: 5, scope: !481)
!491 = !DILocation(line: 273, column: 7, scope: !492)
!492 = distinct !DILexicalBlock(scope: !481, file: !1, line: 273, column: 7)
!493 = !DILocation(line: 273, column: 9, scope: !492)
!494 = !DILocation(line: 273, column: 7, scope: !481)
!495 = !DILocation(line: 274, column: 4, scope: !492)
!496 = !DILocation(line: 275, column: 7, scope: !497)
!497 = distinct !DILexicalBlock(scope: !481, file: !1, line: 275, column: 7)
!498 = !DILocation(line: 275, column: 9, scope: !497)
!499 = !DILocation(line: 275, column: 7, scope: !481)
!500 = !DILocation(line: 276, column: 4, scope: !497)
!501 = !DILocation(line: 280, column: 16, scope: !481)
!502 = !DILocation(line: 280, column: 23, scope: !481)
!503 = !DILocation(line: 280, column: 33, scope: !481)
!504 = !DILocation(line: 280, column: 14, scope: !481)
!505 = !DILocation(line: 281, column: 19, scope: !481)
!506 = !DILocation(line: 281, column: 26, scope: !481)
!507 = !DILocation(line: 281, column: 32, scope: !481)
!508 = !DILocation(line: 281, column: 11, scope: !481)
!509 = !DILocation(line: 281, column: 9, scope: !481)
!510 = !DILocation(line: 282, column: 7, scope: !511)
!511 = distinct !DILexicalBlock(scope: !481, file: !1, line: 282, column: 7)
!512 = !DILocation(line: 282, column: 13, scope: !511)
!513 = !DILocation(line: 282, column: 7, scope: !481)
!514 = !DILocation(line: 283, column: 4, scope: !511)
!515 = !DILocation(line: 284, column: 17, scope: !481)
!516 = !DILocation(line: 284, column: 3, scope: !481)
!517 = !DILocation(line: 284, column: 10, scope: !481)
!518 = !DILocation(line: 284, column: 15, scope: !481)
!519 = !DILocation(line: 285, column: 22, scope: !481)
!520 = !DILocation(line: 285, column: 3, scope: !481)
!521 = !DILocation(line: 285, column: 10, scope: !481)
!522 = !DILocation(line: 285, column: 20, scope: !481)
!523 = !DILocation(line: 269, column: 2, scope: !524)
!524 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 1)
!525 = !DILocation(line: 287, column: 6, scope: !526)
!526 = distinct !DILexicalBlock(scope: !64, file: !1, line: 287, column: 6)
!527 = !DILocation(line: 287, column: 8, scope: !526)
!528 = !DILocation(line: 287, column: 6, scope: !64)
!529 = !DILocation(line: 288, column: 21, scope: !530)
!530 = distinct !DILexicalBlock(scope: !526, file: !1, line: 287, column: 14)
!531 = !DILocation(line: 288, column: 28, scope: !530)
!532 = !DILocation(line: 288, column: 37, scope: !530)
!533 = !DILocation(line: 289, column: 44, scope: !530)
!534 = !DILocation(line: 288, column: 3, scope: !535)
!535 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 1)
!536 = !DILocation(line: 290, column: 3, scope: !530)
!537 = !DILocation(line: 292, column: 6, scope: !538)
!538 = distinct !DILexicalBlock(scope: !64, file: !1, line: 292, column: 6)
!539 = !DILocation(line: 292, column: 13, scope: !538)
!540 = !DILocation(line: 292, column: 6, scope: !64)
!541 = !DILocation(line: 293, column: 3, scope: !538)
!542 = !DILocation(line: 295, column: 16, scope: !64)
!543 = !DILocation(line: 295, column: 24, scope: !64)
!544 = !DILocation(line: 295, column: 9, scope: !64)
!545 = !DILocation(line: 295, column: 2, scope: !64)
!546 = !DILocation(line: 296, column: 1, scope: !64)
