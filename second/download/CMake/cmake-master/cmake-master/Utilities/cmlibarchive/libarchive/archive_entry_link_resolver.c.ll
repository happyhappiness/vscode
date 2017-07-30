; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_link_resolver.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_entry_linkresolver = type { %struct.links_entry**, %struct.links_entry*, i64, i64, i32 }
%struct.links_entry = type { %struct.links_entry*, %struct.links_entry*, %struct.archive_entry*, %struct.archive_entry*, i64, i32 }
%struct.archive_entry = type opaque

; Function Attrs: nounwind uwtable
define %struct.archive_entry_linkresolver* @archive_entry_linkresolver_new() #0 !dbg !14 {
entry:
  %retval = alloca %struct.archive_entry_linkresolver*, align 8
  %res = alloca %struct.archive_entry_linkresolver*, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res, metadata !64, metadata !65), !dbg !66
  %call = call noalias i8* @calloc(i64 1, i64 40) #4, !dbg !67
  %0 = bitcast i8* %call to %struct.archive_entry_linkresolver*, !dbg !67
  store %struct.archive_entry_linkresolver* %0, %struct.archive_entry_linkresolver** %res, align 8, !dbg !68
  %1 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !69
  %cmp = icmp eq %struct.archive_entry_linkresolver* %1, null, !dbg !71
  br i1 %cmp, label %if.then, label %if.end, !dbg !72

if.then:                                          ; preds = %entry
  store %struct.archive_entry_linkresolver* null, %struct.archive_entry_linkresolver** %retval, align 8, !dbg !73
  br label %return, !dbg !73

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !74
  %number_buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %2, i32 0, i32 3, !dbg !75
  store i64 1024, i64* %number_buckets, align 8, !dbg !76
  %3 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !77
  %number_buckets1 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %3, i32 0, i32 3, !dbg !78
  %4 = load i64, i64* %number_buckets1, align 8, !dbg !78
  %call2 = call noalias i8* @calloc(i64 %4, i64 8) #4, !dbg !79
  %5 = bitcast i8* %call2 to %struct.links_entry**, !dbg !79
  %6 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !80
  %buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %6, i32 0, i32 0, !dbg !81
  store %struct.links_entry** %5, %struct.links_entry*** %buckets, align 8, !dbg !82
  %7 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !83
  %buckets3 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %7, i32 0, i32 0, !dbg !85
  %8 = load %struct.links_entry**, %struct.links_entry*** %buckets3, align 8, !dbg !85
  %cmp4 = icmp eq %struct.links_entry** %8, null, !dbg !86
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !87

if.then5:                                         ; preds = %if.end
  %9 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !88
  %10 = bitcast %struct.archive_entry_linkresolver* %9 to i8*, !dbg !88
  call void @free(i8* %10) #4, !dbg !90
  store %struct.archive_entry_linkresolver* null, %struct.archive_entry_linkresolver** %retval, align 8, !dbg !91
  br label %return, !dbg !91

if.end6:                                          ; preds = %if.end
  %11 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res, align 8, !dbg !92
  store %struct.archive_entry_linkresolver* %11, %struct.archive_entry_linkresolver** %retval, align 8, !dbg !93
  br label %return, !dbg !93

return:                                           ; preds = %if.end6, %if.then5, %if.then
  %12 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %retval, align 8, !dbg !94
  ret %struct.archive_entry_linkresolver* %12, !dbg !94
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_linkresolver_set_strategy(%struct.archive_entry_linkresolver* %res, i32 %fmt) #0 !dbg !39 {
entry:
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %fmt.addr = alloca i32, align 4
  %fmtbase = alloca i32, align 4
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !95, metadata !65), !dbg !96
  store i32 %fmt, i32* %fmt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fmt.addr, metadata !97, metadata !65), !dbg !98
  call void @llvm.dbg.declare(metadata i32* %fmtbase, metadata !99, metadata !65), !dbg !100
  %0 = load i32, i32* %fmt.addr, align 4, !dbg !101
  %and = and i32 %0, 16711680, !dbg !102
  store i32 %and, i32* %fmtbase, align 4, !dbg !100
  %1 = load i32, i32* %fmtbase, align 4, !dbg !103
  switch i32 %1, label %sw.default9 [
    i32 917504, label %sw.bb
    i32 458752, label %sw.bb
    i32 327680, label %sw.bb
    i32 65536, label %sw.bb1
    i32 524288, label %sw.bb5
    i32 262144, label %sw.bb7
    i32 131072, label %sw.bb7
    i32 196608, label %sw.bb7
    i32 655360, label %sw.bb7
  ], !dbg !104

sw.bb:                                            ; preds = %entry, %entry, %entry
  %2 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !105
  %strategy = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %2, i32 0, i32 4, !dbg !107
  store i32 2, i32* %strategy, align 8, !dbg !108
  br label %sw.epilog11, !dbg !109

sw.bb1:                                           ; preds = %entry
  %3 = load i32, i32* %fmt.addr, align 4, !dbg !110
  switch i32 %3, label %sw.default [
    i32 65540, label %sw.bb2
    i32 65541, label %sw.bb2
  ], !dbg !111

sw.bb2:                                           ; preds = %sw.bb1, %sw.bb1
  %4 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !112
  %strategy3 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %4, i32 0, i32 4, !dbg !114
  store i32 3, i32* %strategy3, align 8, !dbg !115
  br label %sw.epilog, !dbg !116

sw.default:                                       ; preds = %sw.bb1
  %5 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !117
  %strategy4 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %5, i32 0, i32 4, !dbg !118
  store i32 2, i32* %strategy4, align 8, !dbg !119
  br label %sw.epilog, !dbg !120

sw.epilog:                                        ; preds = %sw.default, %sw.bb2
  br label %sw.epilog11, !dbg !121

sw.bb5:                                           ; preds = %entry
  %6 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !122
  %strategy6 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %6, i32 0, i32 4, !dbg !123
  store i32 1, i32* %strategy6, align 8, !dbg !124
  br label %sw.epilog11, !dbg !125

sw.bb7:                                           ; preds = %entry, %entry, %entry, %entry
  %7 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !126
  %strategy8 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %7, i32 0, i32 4, !dbg !127
  store i32 0, i32* %strategy8, align 8, !dbg !128
  br label %sw.epilog11, !dbg !129

sw.default9:                                      ; preds = %entry
  %8 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !130
  %strategy10 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %8, i32 0, i32 4, !dbg !131
  store i32 2, i32* %strategy10, align 8, !dbg !132
  br label %sw.epilog11, !dbg !133

sw.epilog11:                                      ; preds = %sw.default9, %sw.bb7, %sw.bb5, %sw.epilog, %sw.bb
  ret void, !dbg !134
}

; Function Attrs: nounwind uwtable
define void @archive_entry_linkresolver_free(%struct.archive_entry_linkresolver* %res) #0 !dbg !42 {
entry:
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %le = alloca %struct.links_entry*, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !135, metadata !65), !dbg !136
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !137, metadata !65), !dbg !138
  %0 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !139
  %cmp = icmp eq %struct.archive_entry_linkresolver* %0, null, !dbg !141
  br i1 %cmp, label %if.then, label %if.end, !dbg !142

if.then:                                          ; preds = %entry
  br label %return, !dbg !143

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !144

while.cond:                                       ; preds = %while.body, %if.end
  %1 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !145
  %call = call %struct.links_entry* @next_entry(%struct.archive_entry_linkresolver* %1, i32 3), !dbg !147
  store %struct.links_entry* %call, %struct.links_entry** %le, align 8, !dbg !148
  %cmp1 = icmp ne %struct.links_entry* %call, null, !dbg !149
  br i1 %cmp1, label %while.body, label %while.end, !dbg !150

while.body:                                       ; preds = %while.cond
  %2 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !151
  %entry2 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %2, i32 0, i32 3, !dbg !152
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !152
  call void @archive_entry_free(%struct.archive_entry* %3), !dbg !153
  br label %while.cond, !dbg !154

while.end:                                        ; preds = %while.cond
  %4 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !156
  %buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %4, i32 0, i32 0, !dbg !157
  %5 = load %struct.links_entry**, %struct.links_entry*** %buckets, align 8, !dbg !157
  %6 = bitcast %struct.links_entry** %5 to i8*, !dbg !156
  call void @free(i8* %6) #4, !dbg !158
  %7 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !159
  %8 = bitcast %struct.archive_entry_linkresolver* %7 to i8*, !dbg !159
  call void @free(i8* %8) #4, !dbg !160
  br label %return, !dbg !161

return:                                           ; preds = %while.end, %if.then
  ret void, !dbg !162
}

; Function Attrs: nounwind uwtable
define internal %struct.links_entry* @next_entry(%struct.archive_entry_linkresolver* %res, i32 %mode) #0 !dbg !56 {
entry:
  %retval = alloca %struct.links_entry*, align 8
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %mode.addr = alloca i32, align 4
  %le = alloca %struct.links_entry*, align 8
  %bucket = alloca i64, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !163, metadata !65), !dbg !164
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !165, metadata !65), !dbg !166
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !167, metadata !65), !dbg !168
  call void @llvm.dbg.declare(metadata i64* %bucket, metadata !169, metadata !65), !dbg !170
  %0 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !171
  %spare = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %0, i32 0, i32 1, !dbg !173
  %1 = load %struct.links_entry*, %struct.links_entry** %spare, align 8, !dbg !173
  %cmp = icmp ne %struct.links_entry* %1, null, !dbg !174
  br i1 %cmp, label %if.then, label %if.end, !dbg !175

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !176
  %spare1 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %2, i32 0, i32 1, !dbg !178
  %3 = load %struct.links_entry*, %struct.links_entry** %spare1, align 8, !dbg !178
  %canonical = getelementptr inbounds %struct.links_entry, %struct.links_entry* %3, i32 0, i32 2, !dbg !179
  %4 = load %struct.archive_entry*, %struct.archive_entry** %canonical, align 8, !dbg !179
  call void @archive_entry_free(%struct.archive_entry* %4), !dbg !180
  %5 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !181
  %spare2 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %5, i32 0, i32 1, !dbg !182
  %6 = load %struct.links_entry*, %struct.links_entry** %spare2, align 8, !dbg !182
  %entry3 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %6, i32 0, i32 3, !dbg !183
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry3, align 8, !dbg !183
  call void @archive_entry_free(%struct.archive_entry* %7), !dbg !184
  %8 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !185
  %spare4 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %8, i32 0, i32 1, !dbg !186
  %9 = load %struct.links_entry*, %struct.links_entry** %spare4, align 8, !dbg !186
  %10 = bitcast %struct.links_entry* %9 to i8*, !dbg !185
  call void @free(i8* %10) #4, !dbg !187
  %11 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !188
  %spare5 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %11, i32 0, i32 1, !dbg !189
  store %struct.links_entry* null, %struct.links_entry** %spare5, align 8, !dbg !190
  br label %if.end, !dbg !191

if.end:                                           ; preds = %if.then, %entry
  store i64 0, i64* %bucket, align 8, !dbg !192
  br label %for.cond, !dbg !194

for.cond:                                         ; preds = %for.inc39, %if.end
  %12 = load i64, i64* %bucket, align 8, !dbg !195
  %13 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !198
  %number_buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %13, i32 0, i32 3, !dbg !199
  %14 = load i64, i64* %number_buckets, align 8, !dbg !199
  %cmp6 = icmp ult i64 %12, %14, !dbg !200
  br i1 %cmp6, label %for.body, label %for.end40, !dbg !201

for.body:                                         ; preds = %for.cond
  %15 = load i64, i64* %bucket, align 8, !dbg !202
  %16 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !205
  %buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %16, i32 0, i32 0, !dbg !206
  %17 = load %struct.links_entry**, %struct.links_entry*** %buckets, align 8, !dbg !206
  %arrayidx = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %17, i64 %15, !dbg !205
  %18 = load %struct.links_entry*, %struct.links_entry** %arrayidx, align 8, !dbg !205
  store %struct.links_entry* %18, %struct.links_entry** %le, align 8, !dbg !207
  br label %for.cond7, !dbg !208

for.cond7:                                        ; preds = %for.inc, %for.body
  %19 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !209
  %cmp8 = icmp ne %struct.links_entry* %19, null, !dbg !212
  br i1 %cmp8, label %for.body9, label %for.end, !dbg !213

for.body9:                                        ; preds = %for.cond7
  %20 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !214
  %entry10 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %20, i32 0, i32 3, !dbg !217
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry10, align 8, !dbg !217
  %cmp11 = icmp ne %struct.archive_entry* %21, null, !dbg !218
  br i1 %cmp11, label %land.lhs.true, label %if.end14, !dbg !219

land.lhs.true:                                    ; preds = %for.body9
  %22 = load i32, i32* %mode.addr, align 4, !dbg !220
  %and = and i32 %22, 1, !dbg !221
  %cmp12 = icmp eq i32 %and, 0, !dbg !222
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !223

if.then13:                                        ; preds = %land.lhs.true
  br label %for.inc, !dbg !225

if.end14:                                         ; preds = %land.lhs.true, %for.body9
  %23 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !226
  %entry15 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %23, i32 0, i32 3, !dbg !228
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry15, align 8, !dbg !228
  %cmp16 = icmp eq %struct.archive_entry* %24, null, !dbg !229
  br i1 %cmp16, label %land.lhs.true17, label %if.end21, !dbg !230

land.lhs.true17:                                  ; preds = %if.end14
  %25 = load i32, i32* %mode.addr, align 4, !dbg !231
  %and18 = and i32 %25, 2, !dbg !232
  %cmp19 = icmp eq i32 %and18, 0, !dbg !233
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !234

if.then20:                                        ; preds = %land.lhs.true17
  br label %for.inc, !dbg !235

if.end21:                                         ; preds = %land.lhs.true17, %if.end14
  %26 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !236
  %next = getelementptr inbounds %struct.links_entry, %struct.links_entry* %26, i32 0, i32 0, !dbg !238
  %27 = load %struct.links_entry*, %struct.links_entry** %next, align 8, !dbg !238
  %cmp22 = icmp ne %struct.links_entry* %27, null, !dbg !239
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !240

if.then23:                                        ; preds = %if.end21
  %28 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !241
  %previous = getelementptr inbounds %struct.links_entry, %struct.links_entry* %28, i32 0, i32 1, !dbg !242
  %29 = load %struct.links_entry*, %struct.links_entry** %previous, align 8, !dbg !242
  %30 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !243
  %next24 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %30, i32 0, i32 0, !dbg !244
  %31 = load %struct.links_entry*, %struct.links_entry** %next24, align 8, !dbg !244
  %previous25 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %31, i32 0, i32 1, !dbg !245
  store %struct.links_entry* %29, %struct.links_entry** %previous25, align 8, !dbg !246
  br label %if.end26, !dbg !243

if.end26:                                         ; preds = %if.then23, %if.end21
  %32 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !247
  %previous27 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %32, i32 0, i32 1, !dbg !249
  %33 = load %struct.links_entry*, %struct.links_entry** %previous27, align 8, !dbg !249
  %cmp28 = icmp ne %struct.links_entry* %33, null, !dbg !250
  br i1 %cmp28, label %if.then29, label %if.else, !dbg !251

if.then29:                                        ; preds = %if.end26
  %34 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !252
  %next30 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %34, i32 0, i32 0, !dbg !253
  %35 = load %struct.links_entry*, %struct.links_entry** %next30, align 8, !dbg !253
  %36 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !254
  %previous31 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %36, i32 0, i32 1, !dbg !255
  %37 = load %struct.links_entry*, %struct.links_entry** %previous31, align 8, !dbg !255
  %next32 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %37, i32 0, i32 0, !dbg !256
  store %struct.links_entry* %35, %struct.links_entry** %next32, align 8, !dbg !257
  br label %if.end36, !dbg !254

if.else:                                          ; preds = %if.end26
  %38 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !258
  %next33 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %38, i32 0, i32 0, !dbg !259
  %39 = load %struct.links_entry*, %struct.links_entry** %next33, align 8, !dbg !259
  %40 = load i64, i64* %bucket, align 8, !dbg !260
  %41 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !261
  %buckets34 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %41, i32 0, i32 0, !dbg !262
  %42 = load %struct.links_entry**, %struct.links_entry*** %buckets34, align 8, !dbg !262
  %arrayidx35 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %42, i64 %40, !dbg !261
  store %struct.links_entry* %39, %struct.links_entry** %arrayidx35, align 8, !dbg !263
  br label %if.end36

if.end36:                                         ; preds = %if.else, %if.then29
  %43 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !264
  %number_entries = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %43, i32 0, i32 2, !dbg !265
  %44 = load i64, i64* %number_entries, align 8, !dbg !266
  %dec = add i64 %44, -1, !dbg !266
  store i64 %dec, i64* %number_entries, align 8, !dbg !266
  %45 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !267
  %46 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !268
  %spare37 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %46, i32 0, i32 1, !dbg !269
  store %struct.links_entry* %45, %struct.links_entry** %spare37, align 8, !dbg !270
  %47 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !271
  store %struct.links_entry* %47, %struct.links_entry** %retval, align 8, !dbg !272
  br label %return, !dbg !272

for.inc:                                          ; preds = %if.then20, %if.then13
  %48 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !273
  %next38 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %48, i32 0, i32 0, !dbg !275
  %49 = load %struct.links_entry*, %struct.links_entry** %next38, align 8, !dbg !275
  store %struct.links_entry* %49, %struct.links_entry** %le, align 8, !dbg !276
  br label %for.cond7, !dbg !277

for.end:                                          ; preds = %for.cond7
  br label %for.inc39, !dbg !278

for.inc39:                                        ; preds = %for.end
  %50 = load i64, i64* %bucket, align 8, !dbg !279
  %inc = add i64 %50, 1, !dbg !279
  store i64 %inc, i64* %bucket, align 8, !dbg !279
  br label %for.cond, !dbg !281

for.end40:                                        ; preds = %for.cond
  store %struct.links_entry* null, %struct.links_entry** %retval, align 8, !dbg !282
  br label %return, !dbg !282

return:                                           ; preds = %for.end40, %if.end36
  %51 = load %struct.links_entry*, %struct.links_entry** %retval, align 8, !dbg !283
  ret %struct.links_entry* %51, !dbg !283
}

declare void @archive_entry_free(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define void @archive_entry_linkify(%struct.archive_entry_linkresolver* %res, %struct.archive_entry** %e, %struct.archive_entry** %f) #0 !dbg !45 {
entry:
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %e.addr = alloca %struct.archive_entry**, align 8
  %f.addr = alloca %struct.archive_entry**, align 8
  %le = alloca %struct.links_entry*, align 8
  %t = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !284, metadata !65), !dbg !285
  store %struct.archive_entry** %e, %struct.archive_entry*** %e.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry*** %e.addr, metadata !286, metadata !65), !dbg !287
  store %struct.archive_entry** %f, %struct.archive_entry*** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry*** %f.addr, metadata !288, metadata !65), !dbg !289
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !290, metadata !65), !dbg !291
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %t, metadata !292, metadata !65), !dbg !293
  %0 = load %struct.archive_entry**, %struct.archive_entry*** %f.addr, align 8, !dbg !294
  store %struct.archive_entry* null, %struct.archive_entry** %0, align 8, !dbg !295
  %1 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !296
  %2 = load %struct.archive_entry*, %struct.archive_entry** %1, align 8, !dbg !298
  %cmp = icmp eq %struct.archive_entry* %2, null, !dbg !299
  br i1 %cmp, label %if.then, label %if.end5, !dbg !300

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !301
  %call = call %struct.links_entry* @next_entry(%struct.archive_entry_linkresolver* %3, i32 1), !dbg !303
  store %struct.links_entry* %call, %struct.links_entry** %le, align 8, !dbg !304
  %4 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !305
  %cmp1 = icmp ne %struct.links_entry* %4, null, !dbg !307
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !308

if.then2:                                         ; preds = %if.then
  %5 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !309
  %entry3 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %5, i32 0, i32 3, !dbg !311
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry3, align 8, !dbg !311
  %7 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !312
  store %struct.archive_entry* %6, %struct.archive_entry** %7, align 8, !dbg !313
  %8 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !314
  %entry4 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %8, i32 0, i32 3, !dbg !315
  store %struct.archive_entry* null, %struct.archive_entry** %entry4, align 8, !dbg !316
  br label %if.end, !dbg !317

if.end:                                           ; preds = %if.then2, %if.then
  br label %return, !dbg !318

if.end5:                                          ; preds = %entry
  %9 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !319
  %10 = load %struct.archive_entry*, %struct.archive_entry** %9, align 8, !dbg !321
  %call6 = call i32 @archive_entry_nlink(%struct.archive_entry* %10), !dbg !322
  %cmp7 = icmp eq i32 %call6, 1, !dbg !323
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !324

if.then8:                                         ; preds = %if.end5
  br label %return, !dbg !325

if.end9:                                          ; preds = %if.end5
  %11 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !326
  %12 = load %struct.archive_entry*, %struct.archive_entry** %11, align 8, !dbg !328
  %call10 = call i32 @archive_entry_filetype(%struct.archive_entry* %12), !dbg !329
  %cmp11 = icmp eq i32 %call10, 16384, !dbg !330
  br i1 %cmp11, label %if.then17, label %lor.lhs.false, !dbg !331

lor.lhs.false:                                    ; preds = %if.end9
  %13 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !332
  %14 = load %struct.archive_entry*, %struct.archive_entry** %13, align 8, !dbg !334
  %call12 = call i32 @archive_entry_filetype(%struct.archive_entry* %14), !dbg !335
  %cmp13 = icmp eq i32 %call12, 24576, !dbg !336
  br i1 %cmp13, label %if.then17, label %lor.lhs.false14, !dbg !337

lor.lhs.false14:                                  ; preds = %lor.lhs.false
  %15 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !338
  %16 = load %struct.archive_entry*, %struct.archive_entry** %15, align 8, !dbg !339
  %call15 = call i32 @archive_entry_filetype(%struct.archive_entry* %16), !dbg !340
  %cmp16 = icmp eq i32 %call15, 8192, !dbg !341
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !342

if.then17:                                        ; preds = %lor.lhs.false14, %lor.lhs.false, %if.end9
  br label %return, !dbg !344

if.end18:                                         ; preds = %lor.lhs.false14
  %17 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !345
  %strategy = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %17, i32 0, i32 4, !dbg !346
  %18 = load i32, i32* %strategy, align 8, !dbg !346
  switch i32 %18, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb25
    i32 2, label %sw.bb34
    i32 3, label %sw.bb35
  ], !dbg !347

sw.bb:                                            ; preds = %if.end18
  %19 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !348
  %20 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !350
  %21 = load %struct.archive_entry*, %struct.archive_entry** %20, align 8, !dbg !351
  %call19 = call %struct.links_entry* @find_entry(%struct.archive_entry_linkresolver* %19, %struct.archive_entry* %21), !dbg !352
  store %struct.links_entry* %call19, %struct.links_entry** %le, align 8, !dbg !353
  %22 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !354
  %cmp20 = icmp ne %struct.links_entry* %22, null, !dbg !356
  br i1 %cmp20, label %if.then21, label %if.else, !dbg !357

if.then21:                                        ; preds = %sw.bb
  %23 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !358
  %24 = load %struct.archive_entry*, %struct.archive_entry** %23, align 8, !dbg !360
  call void @archive_entry_unset_size(%struct.archive_entry* %24), !dbg !361
  %25 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !362
  %26 = load %struct.archive_entry*, %struct.archive_entry** %25, align 8, !dbg !363
  %27 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !364
  %canonical = getelementptr inbounds %struct.links_entry, %struct.links_entry* %27, i32 0, i32 2, !dbg !365
  %28 = load %struct.archive_entry*, %struct.archive_entry** %canonical, align 8, !dbg !365
  %call22 = call i8* @archive_entry_pathname(%struct.archive_entry* %28), !dbg !366
  call void @archive_entry_copy_hardlink(%struct.archive_entry* %26, i8* %call22), !dbg !367
  br label %if.end24, !dbg !368

if.else:                                          ; preds = %sw.bb
  %29 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !369
  %30 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !370
  %31 = load %struct.archive_entry*, %struct.archive_entry** %30, align 8, !dbg !371
  %call23 = call %struct.links_entry* @insert_entry(%struct.archive_entry_linkresolver* %29, %struct.archive_entry* %31), !dbg !372
  br label %if.end24

if.end24:                                         ; preds = %if.else, %if.then21
  br label %return, !dbg !373

sw.bb25:                                          ; preds = %if.end18
  %32 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !374
  %33 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !375
  %34 = load %struct.archive_entry*, %struct.archive_entry** %33, align 8, !dbg !376
  %call26 = call %struct.links_entry* @find_entry(%struct.archive_entry_linkresolver* %32, %struct.archive_entry* %34), !dbg !377
  store %struct.links_entry* %call26, %struct.links_entry** %le, align 8, !dbg !378
  %35 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !379
  %cmp27 = icmp ne %struct.links_entry* %35, null, !dbg !381
  br i1 %cmp27, label %if.then28, label %if.else31, !dbg !382

if.then28:                                        ; preds = %sw.bb25
  %36 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !383
  %37 = load %struct.archive_entry*, %struct.archive_entry** %36, align 8, !dbg !385
  %38 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !386
  %canonical29 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %38, i32 0, i32 2, !dbg !387
  %39 = load %struct.archive_entry*, %struct.archive_entry** %canonical29, align 8, !dbg !387
  %call30 = call i8* @archive_entry_pathname(%struct.archive_entry* %39), !dbg !388
  call void @archive_entry_copy_hardlink(%struct.archive_entry* %37, i8* %call30), !dbg !389
  br label %if.end33, !dbg !390

if.else31:                                        ; preds = %sw.bb25
  %40 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !391
  %41 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !392
  %42 = load %struct.archive_entry*, %struct.archive_entry** %41, align 8, !dbg !393
  %call32 = call %struct.links_entry* @insert_entry(%struct.archive_entry_linkresolver* %40, %struct.archive_entry* %42), !dbg !394
  br label %if.end33

if.end33:                                         ; preds = %if.else31, %if.then28
  br label %return, !dbg !395

sw.bb34:                                          ; preds = %if.end18
  br label %return, !dbg !396

sw.bb35:                                          ; preds = %if.end18
  %43 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !397
  %44 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !398
  %45 = load %struct.archive_entry*, %struct.archive_entry** %44, align 8, !dbg !399
  %call36 = call %struct.links_entry* @find_entry(%struct.archive_entry_linkresolver* %43, %struct.archive_entry* %45), !dbg !400
  store %struct.links_entry* %call36, %struct.links_entry** %le, align 8, !dbg !401
  %46 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !402
  %cmp37 = icmp ne %struct.links_entry* %46, null, !dbg !404
  br i1 %cmp37, label %if.then38, label %if.else48, !dbg !405

if.then38:                                        ; preds = %sw.bb35
  %47 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !406
  %48 = load %struct.archive_entry*, %struct.archive_entry** %47, align 8, !dbg !408
  store %struct.archive_entry* %48, %struct.archive_entry** %t, align 8, !dbg !409
  %49 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !410
  %entry39 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %49, i32 0, i32 3, !dbg !411
  %50 = load %struct.archive_entry*, %struct.archive_entry** %entry39, align 8, !dbg !411
  %51 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !412
  store %struct.archive_entry* %50, %struct.archive_entry** %51, align 8, !dbg !413
  %52 = load %struct.archive_entry*, %struct.archive_entry** %t, align 8, !dbg !414
  %53 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !415
  %entry40 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %53, i32 0, i32 3, !dbg !416
  store %struct.archive_entry* %52, %struct.archive_entry** %entry40, align 8, !dbg !417
  %54 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !418
  %55 = load %struct.archive_entry*, %struct.archive_entry** %54, align 8, !dbg !419
  call void @archive_entry_unset_size(%struct.archive_entry* %55), !dbg !420
  %56 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !421
  %57 = load %struct.archive_entry*, %struct.archive_entry** %56, align 8, !dbg !422
  %58 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !423
  %canonical41 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %58, i32 0, i32 2, !dbg !424
  %59 = load %struct.archive_entry*, %struct.archive_entry** %canonical41, align 8, !dbg !424
  %call42 = call i8* @archive_entry_pathname(%struct.archive_entry* %59), !dbg !425
  call void @archive_entry_copy_hardlink(%struct.archive_entry* %57, i8* %call42), !dbg !426
  %60 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !427
  %links = getelementptr inbounds %struct.links_entry, %struct.links_entry* %60, i32 0, i32 5, !dbg !429
  %61 = load i32, i32* %links, align 8, !dbg !429
  %cmp43 = icmp eq i32 %61, 0, !dbg !430
  br i1 %cmp43, label %if.then44, label %if.end47, !dbg !431

if.then44:                                        ; preds = %if.then38
  %62 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !432
  %entry45 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %62, i32 0, i32 3, !dbg !434
  %63 = load %struct.archive_entry*, %struct.archive_entry** %entry45, align 8, !dbg !434
  %64 = load %struct.archive_entry**, %struct.archive_entry*** %f.addr, align 8, !dbg !435
  store %struct.archive_entry* %63, %struct.archive_entry** %64, align 8, !dbg !436
  %65 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !437
  %entry46 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %65, i32 0, i32 3, !dbg !438
  store %struct.archive_entry* null, %struct.archive_entry** %entry46, align 8, !dbg !439
  br label %if.end47, !dbg !440

if.end47:                                         ; preds = %if.then44, %if.then38
  br label %if.end54, !dbg !441

if.else48:                                        ; preds = %sw.bb35
  %66 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !442
  %67 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !444
  %68 = load %struct.archive_entry*, %struct.archive_entry** %67, align 8, !dbg !445
  %call49 = call %struct.links_entry* @insert_entry(%struct.archive_entry_linkresolver* %66, %struct.archive_entry* %68), !dbg !446
  store %struct.links_entry* %call49, %struct.links_entry** %le, align 8, !dbg !447
  %69 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !448
  %cmp50 = icmp eq %struct.links_entry* %69, null, !dbg !450
  br i1 %cmp50, label %if.then51, label %if.end52, !dbg !451

if.then51:                                        ; preds = %if.else48
  br label %return, !dbg !452

if.end52:                                         ; preds = %if.else48
  %70 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !453
  %71 = load %struct.archive_entry*, %struct.archive_entry** %70, align 8, !dbg !454
  %72 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !455
  %entry53 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %72, i32 0, i32 3, !dbg !456
  store %struct.archive_entry* %71, %struct.archive_entry** %entry53, align 8, !dbg !457
  %73 = load %struct.archive_entry**, %struct.archive_entry*** %e.addr, align 8, !dbg !458
  store %struct.archive_entry* null, %struct.archive_entry** %73, align 8, !dbg !459
  br label %if.end54

if.end54:                                         ; preds = %if.end52, %if.end47
  br label %return, !dbg !460

sw.default:                                       ; preds = %if.end18
  br label %sw.epilog, !dbg !461

sw.epilog:                                        ; preds = %sw.default
  br label %return, !dbg !462

return:                                           ; preds = %sw.epilog, %if.end54, %if.then51, %sw.bb34, %if.end33, %if.end24, %if.then17, %if.then8, %if.end
  ret void, !dbg !463
}

declare i32 @archive_entry_nlink(%struct.archive_entry*) #3

declare i32 @archive_entry_filetype(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal %struct.links_entry* @find_entry(%struct.archive_entry_linkresolver* %res, %struct.archive_entry* %entry1) #0 !dbg !53 {
entry:
  %retval = alloca %struct.links_entry*, align 8
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %le = alloca %struct.links_entry*, align 8
  %hash = alloca i64, align 8
  %bucket = alloca i64, align 8
  %dev = alloca i64, align 8
  %ino = alloca i64, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !464, metadata !65), !dbg !465
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !466, metadata !65), !dbg !467
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !468, metadata !65), !dbg !469
  call void @llvm.dbg.declare(metadata i64* %hash, metadata !470, metadata !65), !dbg !471
  call void @llvm.dbg.declare(metadata i64* %bucket, metadata !472, metadata !65), !dbg !473
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !474, metadata !65), !dbg !477
  call void @llvm.dbg.declare(metadata i64* %ino, metadata !478, metadata !65), !dbg !482
  %0 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !483
  %spare = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %0, i32 0, i32 1, !dbg !485
  %1 = load %struct.links_entry*, %struct.links_entry** %spare, align 8, !dbg !485
  %cmp = icmp ne %struct.links_entry* %1, null, !dbg !486
  br i1 %cmp, label %if.then, label %if.end, !dbg !487

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !488
  %spare2 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %2, i32 0, i32 1, !dbg !490
  %3 = load %struct.links_entry*, %struct.links_entry** %spare2, align 8, !dbg !490
  %canonical = getelementptr inbounds %struct.links_entry, %struct.links_entry* %3, i32 0, i32 2, !dbg !491
  %4 = load %struct.archive_entry*, %struct.archive_entry** %canonical, align 8, !dbg !491
  call void @archive_entry_free(%struct.archive_entry* %4), !dbg !492
  %5 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !493
  %spare3 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %5, i32 0, i32 1, !dbg !494
  %6 = load %struct.links_entry*, %struct.links_entry** %spare3, align 8, !dbg !494
  %entry4 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %6, i32 0, i32 3, !dbg !495
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry4, align 8, !dbg !495
  call void @archive_entry_free(%struct.archive_entry* %7), !dbg !496
  %8 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !497
  %spare5 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %8, i32 0, i32 1, !dbg !498
  %9 = load %struct.links_entry*, %struct.links_entry** %spare5, align 8, !dbg !498
  %10 = bitcast %struct.links_entry* %9 to i8*, !dbg !497
  call void @free(i8* %10) #4, !dbg !499
  %11 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !500
  %spare6 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %11, i32 0, i32 1, !dbg !501
  store %struct.links_entry* null, %struct.links_entry** %spare6, align 8, !dbg !502
  br label %if.end, !dbg !503

if.end:                                           ; preds = %if.then, %entry
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !504
  %call = call i64 @archive_entry_dev(%struct.archive_entry* %12), !dbg !505
  store i64 %call, i64* %dev, align 8, !dbg !506
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !507
  %call7 = call i64 @archive_entry_ino64(%struct.archive_entry* %13), !dbg !508
  store i64 %call7, i64* %ino, align 8, !dbg !509
  %14 = load i64, i64* %dev, align 8, !dbg !510
  %15 = load i64, i64* %ino, align 8, !dbg !511
  %xor = xor i64 %14, %15, !dbg !512
  store i64 %xor, i64* %hash, align 8, !dbg !513
  %16 = load i64, i64* %hash, align 8, !dbg !514
  %17 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !515
  %number_buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %17, i32 0, i32 3, !dbg !516
  %18 = load i64, i64* %number_buckets, align 8, !dbg !516
  %sub = sub i64 %18, 1, !dbg !517
  %and = and i64 %16, %sub, !dbg !518
  store i64 %and, i64* %bucket, align 8, !dbg !519
  %19 = load i64, i64* %bucket, align 8, !dbg !520
  %20 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !522
  %buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %20, i32 0, i32 0, !dbg !523
  %21 = load %struct.links_entry**, %struct.links_entry*** %buckets, align 8, !dbg !523
  %arrayidx = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %21, i64 %19, !dbg !522
  %22 = load %struct.links_entry*, %struct.links_entry** %arrayidx, align 8, !dbg !522
  store %struct.links_entry* %22, %struct.links_entry** %le, align 8, !dbg !524
  br label %for.cond, !dbg !525

for.cond:                                         ; preds = %for.inc, %if.end
  %23 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !526
  %cmp8 = icmp ne %struct.links_entry* %23, null, !dbg !529
  br i1 %cmp8, label %for.body, label %for.end, !dbg !530

for.body:                                         ; preds = %for.cond
  %24 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !531
  %hash9 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %24, i32 0, i32 4, !dbg !534
  %25 = load i64, i64* %hash9, align 8, !dbg !534
  %26 = load i64, i64* %hash, align 8, !dbg !535
  %cmp10 = icmp eq i64 %25, %26, !dbg !536
  br i1 %cmp10, label %land.lhs.true, label %if.end45, !dbg !537

land.lhs.true:                                    ; preds = %for.body
  %27 = load i64, i64* %dev, align 8, !dbg !538
  %28 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !540
  %canonical11 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %28, i32 0, i32 2, !dbg !541
  %29 = load %struct.archive_entry*, %struct.archive_entry** %canonical11, align 8, !dbg !541
  %call12 = call i64 @archive_entry_dev(%struct.archive_entry* %29), !dbg !542
  %cmp13 = icmp eq i64 %27, %call12, !dbg !543
  br i1 %cmp13, label %land.lhs.true14, label %if.end45, !dbg !544

land.lhs.true14:                                  ; preds = %land.lhs.true
  %30 = load i64, i64* %ino, align 8, !dbg !545
  %31 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !546
  %canonical15 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %31, i32 0, i32 2, !dbg !547
  %32 = load %struct.archive_entry*, %struct.archive_entry** %canonical15, align 8, !dbg !547
  %call16 = call i64 @archive_entry_ino64(%struct.archive_entry* %32), !dbg !548
  %cmp17 = icmp eq i64 %30, %call16, !dbg !549
  br i1 %cmp17, label %if.then18, label %if.end45, !dbg !550

if.then18:                                        ; preds = %land.lhs.true14
  %33 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !552
  %links = getelementptr inbounds %struct.links_entry, %struct.links_entry* %33, i32 0, i32 5, !dbg !554
  %34 = load i32, i32* %links, align 8, !dbg !555
  %dec = add i32 %34, -1, !dbg !555
  store i32 %dec, i32* %links, align 8, !dbg !555
  %35 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !556
  %links19 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %35, i32 0, i32 5, !dbg !558
  %36 = load i32, i32* %links19, align 8, !dbg !558
  %cmp20 = icmp ugt i32 %36, 0, !dbg !559
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !560

if.then21:                                        ; preds = %if.then18
  %37 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !561
  store %struct.links_entry* %37, %struct.links_entry** %retval, align 8, !dbg !562
  br label %return, !dbg !562

if.end22:                                         ; preds = %if.then18
  %38 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !563
  %previous = getelementptr inbounds %struct.links_entry, %struct.links_entry* %38, i32 0, i32 1, !dbg !565
  %39 = load %struct.links_entry*, %struct.links_entry** %previous, align 8, !dbg !565
  %cmp23 = icmp ne %struct.links_entry* %39, null, !dbg !566
  br i1 %cmp23, label %if.then24, label %if.end27, !dbg !567

if.then24:                                        ; preds = %if.end22
  %40 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !568
  %next = getelementptr inbounds %struct.links_entry, %struct.links_entry* %40, i32 0, i32 0, !dbg !569
  %41 = load %struct.links_entry*, %struct.links_entry** %next, align 8, !dbg !569
  %42 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !570
  %previous25 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %42, i32 0, i32 1, !dbg !571
  %43 = load %struct.links_entry*, %struct.links_entry** %previous25, align 8, !dbg !571
  %next26 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %43, i32 0, i32 0, !dbg !572
  store %struct.links_entry* %41, %struct.links_entry** %next26, align 8, !dbg !573
  br label %if.end27, !dbg !570

if.end27:                                         ; preds = %if.then24, %if.end22
  %44 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !574
  %next28 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %44, i32 0, i32 0, !dbg !576
  %45 = load %struct.links_entry*, %struct.links_entry** %next28, align 8, !dbg !576
  %cmp29 = icmp ne %struct.links_entry* %45, null, !dbg !577
  br i1 %cmp29, label %if.then30, label %if.end34, !dbg !578

if.then30:                                        ; preds = %if.end27
  %46 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !579
  %previous31 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %46, i32 0, i32 1, !dbg !580
  %47 = load %struct.links_entry*, %struct.links_entry** %previous31, align 8, !dbg !580
  %48 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !581
  %next32 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %48, i32 0, i32 0, !dbg !582
  %49 = load %struct.links_entry*, %struct.links_entry** %next32, align 8, !dbg !582
  %previous33 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %49, i32 0, i32 1, !dbg !583
  store %struct.links_entry* %47, %struct.links_entry** %previous33, align 8, !dbg !584
  br label %if.end34, !dbg !581

if.end34:                                         ; preds = %if.then30, %if.end27
  %50 = load i64, i64* %bucket, align 8, !dbg !585
  %51 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !587
  %buckets35 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %51, i32 0, i32 0, !dbg !588
  %52 = load %struct.links_entry**, %struct.links_entry*** %buckets35, align 8, !dbg !588
  %arrayidx36 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %52, i64 %50, !dbg !587
  %53 = load %struct.links_entry*, %struct.links_entry** %arrayidx36, align 8, !dbg !587
  %54 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !589
  %cmp37 = icmp eq %struct.links_entry* %53, %54, !dbg !590
  br i1 %cmp37, label %if.then38, label %if.end42, !dbg !591

if.then38:                                        ; preds = %if.end34
  %55 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !592
  %next39 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %55, i32 0, i32 0, !dbg !593
  %56 = load %struct.links_entry*, %struct.links_entry** %next39, align 8, !dbg !593
  %57 = load i64, i64* %bucket, align 8, !dbg !594
  %58 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !595
  %buckets40 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %58, i32 0, i32 0, !dbg !596
  %59 = load %struct.links_entry**, %struct.links_entry*** %buckets40, align 8, !dbg !596
  %arrayidx41 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %59, i64 %57, !dbg !595
  store %struct.links_entry* %56, %struct.links_entry** %arrayidx41, align 8, !dbg !597
  br label %if.end42, !dbg !595

if.end42:                                         ; preds = %if.then38, %if.end34
  %60 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !598
  %number_entries = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %60, i32 0, i32 2, !dbg !599
  %61 = load i64, i64* %number_entries, align 8, !dbg !600
  %dec43 = add i64 %61, -1, !dbg !600
  store i64 %dec43, i64* %number_entries, align 8, !dbg !600
  %62 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !601
  %63 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !602
  %spare44 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %63, i32 0, i32 1, !dbg !603
  store %struct.links_entry* %62, %struct.links_entry** %spare44, align 8, !dbg !604
  %64 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !605
  store %struct.links_entry* %64, %struct.links_entry** %retval, align 8, !dbg !606
  br label %return, !dbg !606

if.end45:                                         ; preds = %land.lhs.true14, %land.lhs.true, %for.body
  br label %for.inc, !dbg !607

for.inc:                                          ; preds = %if.end45
  %65 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !608
  %next46 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %65, i32 0, i32 0, !dbg !610
  %66 = load %struct.links_entry*, %struct.links_entry** %next46, align 8, !dbg !610
  store %struct.links_entry* %66, %struct.links_entry** %le, align 8, !dbg !611
  br label %for.cond, !dbg !612

for.end:                                          ; preds = %for.cond
  store %struct.links_entry* null, %struct.links_entry** %retval, align 8, !dbg !613
  br label %return, !dbg !613

return:                                           ; preds = %for.end, %if.end42, %if.then21
  %67 = load %struct.links_entry*, %struct.links_entry** %retval, align 8, !dbg !614
  ret %struct.links_entry* %67, !dbg !614
}

declare void @archive_entry_unset_size(%struct.archive_entry*) #3

declare void @archive_entry_copy_hardlink(%struct.archive_entry*, i8*) #3

declare i8* @archive_entry_pathname(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal %struct.links_entry* @insert_entry(%struct.archive_entry_linkresolver* %res, %struct.archive_entry* %entry1) #0 !dbg !59 {
entry:
  %retval = alloca %struct.links_entry*, align 8
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %le = alloca %struct.links_entry*, align 8
  %hash = alloca i64, align 8
  %bucket = alloca i64, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !615, metadata !65), !dbg !616
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !617, metadata !65), !dbg !618
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !619, metadata !65), !dbg !620
  call void @llvm.dbg.declare(metadata i64* %hash, metadata !621, metadata !65), !dbg !622
  call void @llvm.dbg.declare(metadata i64* %bucket, metadata !623, metadata !65), !dbg !624
  %call = call noalias i8* @calloc(i64 1, i64 48) #4, !dbg !625
  %0 = bitcast i8* %call to %struct.links_entry*, !dbg !625
  store %struct.links_entry* %0, %struct.links_entry** %le, align 8, !dbg !626
  %1 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !627
  %cmp = icmp eq %struct.links_entry* %1, null, !dbg !629
  br i1 %cmp, label %if.then, label %if.end, !dbg !630

if.then:                                          ; preds = %entry
  store %struct.links_entry* null, %struct.links_entry** %retval, align 8, !dbg !631
  br label %return, !dbg !631

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !632
  %call2 = call %struct.archive_entry* @archive_entry_clone(%struct.archive_entry* %2), !dbg !633
  %3 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !634
  %canonical = getelementptr inbounds %struct.links_entry, %struct.links_entry* %3, i32 0, i32 2, !dbg !635
  store %struct.archive_entry* %call2, %struct.archive_entry** %canonical, align 8, !dbg !636
  %4 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !637
  %number_entries = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %4, i32 0, i32 2, !dbg !639
  %5 = load i64, i64* %number_entries, align 8, !dbg !639
  %6 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !640
  %number_buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %6, i32 0, i32 3, !dbg !641
  %7 = load i64, i64* %number_buckets, align 8, !dbg !641
  %mul = mul i64 %7, 2, !dbg !642
  %cmp3 = icmp ugt i64 %5, %mul, !dbg !643
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !644

if.then4:                                         ; preds = %if.end
  %8 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !645
  call void @grow_hash(%struct.archive_entry_linkresolver* %8), !dbg !646
  br label %if.end5, !dbg !646

if.end5:                                          ; preds = %if.then4, %if.end
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !647
  %call6 = call i64 @archive_entry_dev(%struct.archive_entry* %9), !dbg !648
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !649
  %call7 = call i64 @archive_entry_ino64(%struct.archive_entry* %10), !dbg !650
  %xor = xor i64 %call6, %call7, !dbg !652
  store i64 %xor, i64* %hash, align 8, !dbg !653
  %11 = load i64, i64* %hash, align 8, !dbg !654
  %12 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !655
  %number_buckets8 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %12, i32 0, i32 3, !dbg !656
  %13 = load i64, i64* %number_buckets8, align 8, !dbg !656
  %sub = sub i64 %13, 1, !dbg !657
  %and = and i64 %11, %sub, !dbg !658
  store i64 %and, i64* %bucket, align 8, !dbg !659
  %14 = load i64, i64* %bucket, align 8, !dbg !660
  %15 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !662
  %buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %15, i32 0, i32 0, !dbg !663
  %16 = load %struct.links_entry**, %struct.links_entry*** %buckets, align 8, !dbg !663
  %arrayidx = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %16, i64 %14, !dbg !662
  %17 = load %struct.links_entry*, %struct.links_entry** %arrayidx, align 8, !dbg !662
  %cmp9 = icmp ne %struct.links_entry* %17, null, !dbg !664
  br i1 %cmp9, label %if.then10, label %if.end13, !dbg !665

if.then10:                                        ; preds = %if.end5
  %18 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !666
  %19 = load i64, i64* %bucket, align 8, !dbg !667
  %20 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !668
  %buckets11 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %20, i32 0, i32 0, !dbg !669
  %21 = load %struct.links_entry**, %struct.links_entry*** %buckets11, align 8, !dbg !669
  %arrayidx12 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %21, i64 %19, !dbg !668
  %22 = load %struct.links_entry*, %struct.links_entry** %arrayidx12, align 8, !dbg !668
  %previous = getelementptr inbounds %struct.links_entry, %struct.links_entry* %22, i32 0, i32 1, !dbg !670
  store %struct.links_entry* %18, %struct.links_entry** %previous, align 8, !dbg !671
  br label %if.end13, !dbg !668

if.end13:                                         ; preds = %if.then10, %if.end5
  %23 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !672
  %number_entries14 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %23, i32 0, i32 2, !dbg !673
  %24 = load i64, i64* %number_entries14, align 8, !dbg !674
  %inc = add i64 %24, 1, !dbg !674
  store i64 %inc, i64* %number_entries14, align 8, !dbg !674
  %25 = load i64, i64* %bucket, align 8, !dbg !675
  %26 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !676
  %buckets15 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %26, i32 0, i32 0, !dbg !677
  %27 = load %struct.links_entry**, %struct.links_entry*** %buckets15, align 8, !dbg !677
  %arrayidx16 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %27, i64 %25, !dbg !676
  %28 = load %struct.links_entry*, %struct.links_entry** %arrayidx16, align 8, !dbg !676
  %29 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !678
  %next = getelementptr inbounds %struct.links_entry, %struct.links_entry* %29, i32 0, i32 0, !dbg !679
  store %struct.links_entry* %28, %struct.links_entry** %next, align 8, !dbg !680
  %30 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !681
  %previous17 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %30, i32 0, i32 1, !dbg !682
  store %struct.links_entry* null, %struct.links_entry** %previous17, align 8, !dbg !683
  %31 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !684
  %32 = load i64, i64* %bucket, align 8, !dbg !685
  %33 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !686
  %buckets18 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %33, i32 0, i32 0, !dbg !687
  %34 = load %struct.links_entry**, %struct.links_entry*** %buckets18, align 8, !dbg !687
  %arrayidx19 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %34, i64 %32, !dbg !686
  store %struct.links_entry* %31, %struct.links_entry** %arrayidx19, align 8, !dbg !688
  %35 = load i64, i64* %hash, align 8, !dbg !689
  %36 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !690
  %hash20 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %36, i32 0, i32 4, !dbg !691
  store i64 %35, i64* %hash20, align 8, !dbg !692
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !693
  %call21 = call i32 @archive_entry_nlink(%struct.archive_entry* %37), !dbg !694
  %sub22 = sub i32 %call21, 1, !dbg !695
  %38 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !696
  %links = getelementptr inbounds %struct.links_entry, %struct.links_entry* %38, i32 0, i32 5, !dbg !697
  store i32 %sub22, i32* %links, align 8, !dbg !698
  %39 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !699
  store %struct.links_entry* %39, %struct.links_entry** %retval, align 8, !dbg !700
  br label %return, !dbg !700

return:                                           ; preds = %if.end13, %if.then
  %40 = load %struct.links_entry*, %struct.links_entry** %retval, align 8, !dbg !701
  ret %struct.links_entry* %40, !dbg !701
}

; Function Attrs: nounwind uwtable
define %struct.archive_entry* @archive_entry_partial_links(%struct.archive_entry_linkresolver* %res, i32* %links) #0 !dbg !49 {
entry:
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %links.addr = alloca i32*, align 8
  %e = alloca %struct.archive_entry*, align 8
  %le = alloca %struct.links_entry*, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !702, metadata !65), !dbg !703
  store i32* %links, i32** %links.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %links.addr, metadata !704, metadata !65), !dbg !705
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %e, metadata !706, metadata !65), !dbg !707
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !708, metadata !65), !dbg !709
  %0 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !710
  %spare = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %0, i32 0, i32 1, !dbg !712
  %1 = load %struct.links_entry*, %struct.links_entry** %spare, align 8, !dbg !712
  %cmp = icmp ne %struct.links_entry* %1, null, !dbg !713
  br i1 %cmp, label %if.then, label %if.end, !dbg !714

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !715
  %spare1 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %2, i32 0, i32 1, !dbg !717
  %3 = load %struct.links_entry*, %struct.links_entry** %spare1, align 8, !dbg !717
  %canonical = getelementptr inbounds %struct.links_entry, %struct.links_entry* %3, i32 0, i32 2, !dbg !718
  %4 = load %struct.archive_entry*, %struct.archive_entry** %canonical, align 8, !dbg !718
  call void @archive_entry_free(%struct.archive_entry* %4), !dbg !719
  %5 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !720
  %spare2 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %5, i32 0, i32 1, !dbg !721
  %6 = load %struct.links_entry*, %struct.links_entry** %spare2, align 8, !dbg !721
  %entry3 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %6, i32 0, i32 3, !dbg !722
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry3, align 8, !dbg !722
  call void @archive_entry_free(%struct.archive_entry* %7), !dbg !723
  %8 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !724
  %spare4 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %8, i32 0, i32 1, !dbg !725
  %9 = load %struct.links_entry*, %struct.links_entry** %spare4, align 8, !dbg !725
  %10 = bitcast %struct.links_entry* %9 to i8*, !dbg !724
  call void @free(i8* %10) #4, !dbg !726
  %11 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !727
  %spare5 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %11, i32 0, i32 1, !dbg !728
  store %struct.links_entry* null, %struct.links_entry** %spare5, align 8, !dbg !729
  br label %if.end, !dbg !730

if.end:                                           ; preds = %if.then, %entry
  %12 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !731
  %call = call %struct.links_entry* @next_entry(%struct.archive_entry_linkresolver* %12, i32 2), !dbg !732
  store %struct.links_entry* %call, %struct.links_entry** %le, align 8, !dbg !733
  %13 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !734
  %cmp6 = icmp ne %struct.links_entry* %13, null, !dbg !736
  br i1 %cmp6, label %if.then7, label %if.else, !dbg !737

if.then7:                                         ; preds = %if.end
  %14 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !738
  %canonical8 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %14, i32 0, i32 2, !dbg !740
  %15 = load %struct.archive_entry*, %struct.archive_entry** %canonical8, align 8, !dbg !740
  store %struct.archive_entry* %15, %struct.archive_entry** %e, align 8, !dbg !741
  %16 = load i32*, i32** %links.addr, align 8, !dbg !742
  %cmp9 = icmp ne i32* %16, null, !dbg !744
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !745

if.then10:                                        ; preds = %if.then7
  %17 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !746
  %links11 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %17, i32 0, i32 5, !dbg !747
  %18 = load i32, i32* %links11, align 8, !dbg !747
  %19 = load i32*, i32** %links.addr, align 8, !dbg !748
  store i32 %18, i32* %19, align 4, !dbg !749
  br label %if.end12, !dbg !750

if.end12:                                         ; preds = %if.then10, %if.then7
  %20 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !751
  %canonical13 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %20, i32 0, i32 2, !dbg !752
  store %struct.archive_entry* null, %struct.archive_entry** %canonical13, align 8, !dbg !753
  br label %if.end17, !dbg !754

if.else:                                          ; preds = %if.end
  store %struct.archive_entry* null, %struct.archive_entry** %e, align 8, !dbg !755
  %21 = load i32*, i32** %links.addr, align 8, !dbg !757
  %cmp14 = icmp ne i32* %21, null, !dbg !759
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !760

if.then15:                                        ; preds = %if.else
  %22 = load i32*, i32** %links.addr, align 8, !dbg !761
  store i32 0, i32* %22, align 4, !dbg !762
  br label %if.end16, !dbg !763

if.end16:                                         ; preds = %if.then15, %if.else
  br label %if.end17

if.end17:                                         ; preds = %if.end16, %if.end12
  %23 = load %struct.archive_entry*, %struct.archive_entry** %e, align 8, !dbg !764
  ret %struct.archive_entry* %23, !dbg !765
}

declare i64 @archive_entry_dev(%struct.archive_entry*) #3

declare i64 @archive_entry_ino64(%struct.archive_entry*) #3

declare %struct.archive_entry* @archive_entry_clone(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal void @grow_hash(%struct.archive_entry_linkresolver* %res) #0 !dbg !60 {
entry:
  %res.addr = alloca %struct.archive_entry_linkresolver*, align 8
  %le = alloca %struct.links_entry*, align 8
  %new_buckets = alloca %struct.links_entry**, align 8
  %new_size = alloca i64, align 8
  %i = alloca i64, align 8
  %bucket = alloca i64, align 8
  store %struct.archive_entry_linkresolver* %res, %struct.archive_entry_linkresolver** %res.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_linkresolver** %res.addr, metadata !766, metadata !65), !dbg !767
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !768, metadata !65), !dbg !769
  call void @llvm.dbg.declare(metadata %struct.links_entry*** %new_buckets, metadata !770, metadata !65), !dbg !771
  call void @llvm.dbg.declare(metadata i64* %new_size, metadata !772, metadata !65), !dbg !773
  call void @llvm.dbg.declare(metadata i64* %i, metadata !774, metadata !65), !dbg !775
  call void @llvm.dbg.declare(metadata i64* %bucket, metadata !776, metadata !65), !dbg !777
  %0 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !778
  %number_buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %0, i32 0, i32 3, !dbg !779
  %1 = load i64, i64* %number_buckets, align 8, !dbg !779
  %mul = mul i64 %1, 2, !dbg !780
  store i64 %mul, i64* %new_size, align 8, !dbg !781
  %2 = load i64, i64* %new_size, align 8, !dbg !782
  %3 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !784
  %number_buckets1 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %3, i32 0, i32 3, !dbg !785
  %4 = load i64, i64* %number_buckets1, align 8, !dbg !785
  %cmp = icmp ult i64 %2, %4, !dbg !786
  br i1 %cmp, label %if.then, label %if.end, !dbg !787

if.then:                                          ; preds = %entry
  br label %return, !dbg !788

if.end:                                           ; preds = %entry
  %5 = load i64, i64* %new_size, align 8, !dbg !789
  %call = call noalias i8* @calloc(i64 %5, i64 8) #4, !dbg !790
  %6 = bitcast i8* %call to %struct.links_entry**, !dbg !790
  store %struct.links_entry** %6, %struct.links_entry*** %new_buckets, align 8, !dbg !791
  %7 = load %struct.links_entry**, %struct.links_entry*** %new_buckets, align 8, !dbg !792
  %cmp2 = icmp eq %struct.links_entry** %7, null, !dbg !794
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !795

if.then3:                                         ; preds = %if.end
  br label %return, !dbg !796

if.end4:                                          ; preds = %if.end
  store i64 0, i64* %i, align 8, !dbg !797
  br label %for.cond, !dbg !799

for.cond:                                         ; preds = %for.inc, %if.end4
  %8 = load i64, i64* %i, align 8, !dbg !800
  %9 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !803
  %number_buckets5 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %9, i32 0, i32 3, !dbg !804
  %10 = load i64, i64* %number_buckets5, align 8, !dbg !804
  %cmp6 = icmp ult i64 %8, %10, !dbg !805
  br i1 %cmp6, label %for.body, label %for.end, !dbg !806

for.body:                                         ; preds = %for.cond
  br label %while.cond, !dbg !807

while.cond:                                       ; preds = %if.end16, %for.body
  %11 = load i64, i64* %i, align 8, !dbg !809
  %12 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !811
  %buckets = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %12, i32 0, i32 0, !dbg !812
  %13 = load %struct.links_entry**, %struct.links_entry*** %buckets, align 8, !dbg !812
  %arrayidx = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %13, i64 %11, !dbg !811
  %14 = load %struct.links_entry*, %struct.links_entry** %arrayidx, align 8, !dbg !811
  %cmp7 = icmp ne %struct.links_entry* %14, null, !dbg !813
  br i1 %cmp7, label %while.body, label %while.end, !dbg !814

while.body:                                       ; preds = %while.cond
  %15 = load i64, i64* %i, align 8, !dbg !815
  %16 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !817
  %buckets8 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %16, i32 0, i32 0, !dbg !818
  %17 = load %struct.links_entry**, %struct.links_entry*** %buckets8, align 8, !dbg !818
  %arrayidx9 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %17, i64 %15, !dbg !817
  %18 = load %struct.links_entry*, %struct.links_entry** %arrayidx9, align 8, !dbg !817
  store %struct.links_entry* %18, %struct.links_entry** %le, align 8, !dbg !819
  %19 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !820
  %next = getelementptr inbounds %struct.links_entry, %struct.links_entry* %19, i32 0, i32 0, !dbg !821
  %20 = load %struct.links_entry*, %struct.links_entry** %next, align 8, !dbg !821
  %21 = load i64, i64* %i, align 8, !dbg !822
  %22 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !823
  %buckets10 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %22, i32 0, i32 0, !dbg !824
  %23 = load %struct.links_entry**, %struct.links_entry*** %buckets10, align 8, !dbg !824
  %arrayidx11 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %23, i64 %21, !dbg !823
  store %struct.links_entry* %20, %struct.links_entry** %arrayidx11, align 8, !dbg !825
  %24 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !826
  %hash = getelementptr inbounds %struct.links_entry, %struct.links_entry* %24, i32 0, i32 4, !dbg !827
  %25 = load i64, i64* %hash, align 8, !dbg !827
  %26 = load i64, i64* %new_size, align 8, !dbg !828
  %sub = sub i64 %26, 1, !dbg !829
  %and = and i64 %25, %sub, !dbg !830
  store i64 %and, i64* %bucket, align 8, !dbg !831
  %27 = load i64, i64* %bucket, align 8, !dbg !832
  %28 = load %struct.links_entry**, %struct.links_entry*** %new_buckets, align 8, !dbg !834
  %arrayidx12 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %28, i64 %27, !dbg !834
  %29 = load %struct.links_entry*, %struct.links_entry** %arrayidx12, align 8, !dbg !834
  %cmp13 = icmp ne %struct.links_entry* %29, null, !dbg !835
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !836

if.then14:                                        ; preds = %while.body
  %30 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !837
  %31 = load i64, i64* %bucket, align 8, !dbg !838
  %32 = load %struct.links_entry**, %struct.links_entry*** %new_buckets, align 8, !dbg !839
  %arrayidx15 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %32, i64 %31, !dbg !839
  %33 = load %struct.links_entry*, %struct.links_entry** %arrayidx15, align 8, !dbg !839
  %previous = getelementptr inbounds %struct.links_entry, %struct.links_entry* %33, i32 0, i32 1, !dbg !840
  store %struct.links_entry* %30, %struct.links_entry** %previous, align 8, !dbg !841
  br label %if.end16, !dbg !839

if.end16:                                         ; preds = %if.then14, %while.body
  %34 = load i64, i64* %bucket, align 8, !dbg !842
  %35 = load %struct.links_entry**, %struct.links_entry*** %new_buckets, align 8, !dbg !843
  %arrayidx17 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %35, i64 %34, !dbg !843
  %36 = load %struct.links_entry*, %struct.links_entry** %arrayidx17, align 8, !dbg !843
  %37 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !844
  %next18 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %37, i32 0, i32 0, !dbg !845
  store %struct.links_entry* %36, %struct.links_entry** %next18, align 8, !dbg !846
  %38 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !847
  %previous19 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %38, i32 0, i32 1, !dbg !848
  store %struct.links_entry* null, %struct.links_entry** %previous19, align 8, !dbg !849
  %39 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !850
  %40 = load i64, i64* %bucket, align 8, !dbg !851
  %41 = load %struct.links_entry**, %struct.links_entry*** %new_buckets, align 8, !dbg !852
  %arrayidx20 = getelementptr inbounds %struct.links_entry*, %struct.links_entry** %41, i64 %40, !dbg !852
  store %struct.links_entry* %39, %struct.links_entry** %arrayidx20, align 8, !dbg !853
  br label %while.cond, !dbg !854

while.end:                                        ; preds = %while.cond
  br label %for.inc, !dbg !856

for.inc:                                          ; preds = %while.end
  %42 = load i64, i64* %i, align 8, !dbg !857
  %inc = add i64 %42, 1, !dbg !857
  store i64 %inc, i64* %i, align 8, !dbg !857
  br label %for.cond, !dbg !859

for.end:                                          ; preds = %for.cond
  %43 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !860
  %buckets21 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %43, i32 0, i32 0, !dbg !861
  %44 = load %struct.links_entry**, %struct.links_entry*** %buckets21, align 8, !dbg !861
  %45 = bitcast %struct.links_entry** %44 to i8*, !dbg !860
  call void @free(i8* %45) #4, !dbg !862
  %46 = load %struct.links_entry**, %struct.links_entry*** %new_buckets, align 8, !dbg !863
  %47 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !864
  %buckets22 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %47, i32 0, i32 0, !dbg !865
  store %struct.links_entry** %46, %struct.links_entry*** %buckets22, align 8, !dbg !866
  %48 = load i64, i64* %new_size, align 8, !dbg !867
  %49 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %res.addr, align 8, !dbg !868
  %number_buckets23 = getelementptr inbounds %struct.archive_entry_linkresolver, %struct.archive_entry_linkresolver* %49, i32 0, i32 3, !dbg !869
  store i64 %48, i64* %number_buckets23, align 8, !dbg !870
  br label %return, !dbg !871

return:                                           ; preds = %for.end, %if.then3, %if.then
  ret void, !dbg !872
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!61, !62}
!llvm.ident = !{!63}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !13)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_link_resolver.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !10}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !6, line: 63, baseType: !7)
!6 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !8, line: 129, baseType: !9)
!8 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!10 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !11, line: 62, baseType: !12)
!11 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!12 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!13 = !{!14, !39, !42, !45, !49, !53, !56, !59, !60}
!14 = distinct !DISubprogram(name: "archive_entry_linkresolver_new", scope: !1, file: !1, line: 100, type: !15, isLocal: false, isDefinition: true, scopeLine: 101, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{!17}
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry_linkresolver", file: !1, line: 79, size: 320, align: 64, elements: !19)
!19 = !{!20, !34, !35, !36, !37}
!20 = !DIDerivedType(tag: DW_TAG_member, name: "buckets", scope: !18, file: !1, line: 80, baseType: !21, size: 64, align: 64)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DICompositeType(tag: DW_TAG_structure_type, name: "links_entry", file: !1, line: 70, size: 384, align: 64, elements: !24)
!24 = !{!25, !26, !27, !31, !32, !33}
!25 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !23, file: !1, line: 71, baseType: !22, size: 64, align: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "previous", scope: !23, file: !1, line: 72, baseType: !22, size: 64, align: 64, offset: 64)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "canonical", scope: !23, file: !1, line: 73, baseType: !28, size: 64, align: 64, offset: 128)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !30, line: 180, flags: DIFlagFwdDecl)
!30 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!31 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !23, file: !1, line: 74, baseType: !28, size: 64, align: 64, offset: 192)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !23, file: !1, line: 75, baseType: !10, size: 64, align: 64, offset: 256)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "links", scope: !23, file: !1, line: 76, baseType: !9, size: 32, align: 32, offset: 320)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "spare", scope: !18, file: !1, line: 81, baseType: !22, size: 64, align: 64, offset: 64)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "number_entries", scope: !18, file: !1, line: 82, baseType: !12, size: 64, align: 64, offset: 128)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "number_buckets", scope: !18, file: !1, line: 83, baseType: !10, size: 64, align: 64, offset: 192)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "strategy", scope: !18, file: !1, line: 84, baseType: !38, size: 32, align: 32, offset: 256)
!38 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!39 = distinct !DISubprogram(name: "archive_entry_linkresolver_set_strategy", scope: !1, file: !1, line: 122, type: !40, isLocal: false, isDefinition: true, scopeLine: 124, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!40 = !DISubroutineType(types: !41)
!41 = !{null, !17, !38}
!42 = distinct !DISubprogram(name: "archive_entry_linkresolver_free", scope: !1, file: !1, line: 160, type: !43, isLocal: false, isDefinition: true, scopeLine: 161, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!43 = !DISubroutineType(types: !44)
!44 = !{null, !17}
!45 = distinct !DISubprogram(name: "archive_entry_linkify", scope: !1, file: !1, line: 174, type: !46, isLocal: false, isDefinition: true, scopeLine: 176, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!46 = !DISubroutineType(types: !47)
!47 = !{null, !17, !48, !48}
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!49 = distinct !DISubprogram(name: "archive_entry_partial_links", scope: !1, file: !1, line: 421, type: !50, isLocal: false, isDefinition: true, scopeLine: 423, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!50 = !DISubroutineType(types: !51)
!51 = !{!28, !17, !52}
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!53 = distinct !DISubprogram(name: "find_entry", scope: !1, file: !1, line: 261, type: !54, isLocal: true, isDefinition: true, scopeLine: 263, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!54 = !DISubroutineType(types: !55)
!55 = !{!22, !17, !28}
!56 = distinct !DISubprogram(name: "next_entry", scope: !1, file: !1, line: 313, type: !57, isLocal: true, isDefinition: true, scopeLine: 314, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!57 = !DISubroutineType(types: !58)
!58 = !{!22, !17, !38}
!59 = distinct !DISubprogram(name: "insert_entry", scope: !1, file: !1, line: 352, type: !54, isLocal: true, isDefinition: true, scopeLine: 354, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!60 = distinct !DISubprogram(name: "grow_hash", scope: !1, file: !1, line: 384, type: !43, isLocal: true, isDefinition: true, scopeLine: 385, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!61 = !{i32 2, !"Dwarf Version", i32 4}
!62 = !{i32 2, !"Debug Info Version", i32 3}
!63 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!64 = !DILocalVariable(name: "res", scope: !14, file: !1, line: 102, type: !17)
!65 = !DIExpression()
!66 = !DILocation(line: 102, column: 37, scope: !14)
!67 = !DILocation(line: 109, column: 8, scope: !14)
!68 = !DILocation(line: 109, column: 6, scope: !14)
!69 = !DILocation(line: 110, column: 6, scope: !70)
!70 = distinct !DILexicalBlock(scope: !14, file: !1, line: 110, column: 6)
!71 = !DILocation(line: 110, column: 10, scope: !70)
!72 = !DILocation(line: 110, column: 6, scope: !14)
!73 = !DILocation(line: 111, column: 3, scope: !70)
!74 = !DILocation(line: 112, column: 2, scope: !14)
!75 = !DILocation(line: 112, column: 7, scope: !14)
!76 = !DILocation(line: 112, column: 22, scope: !14)
!77 = !DILocation(line: 113, column: 24, scope: !14)
!78 = !DILocation(line: 113, column: 29, scope: !14)
!79 = !DILocation(line: 113, column: 17, scope: !14)
!80 = !DILocation(line: 113, column: 2, scope: !14)
!81 = !DILocation(line: 113, column: 7, scope: !14)
!82 = !DILocation(line: 113, column: 15, scope: !14)
!83 = !DILocation(line: 114, column: 6, scope: !84)
!84 = distinct !DILexicalBlock(scope: !14, file: !1, line: 114, column: 6)
!85 = !DILocation(line: 114, column: 11, scope: !84)
!86 = !DILocation(line: 114, column: 19, scope: !84)
!87 = !DILocation(line: 114, column: 6, scope: !14)
!88 = !DILocation(line: 115, column: 8, scope: !89)
!89 = distinct !DILexicalBlock(scope: !84, file: !1, line: 114, column: 28)
!90 = !DILocation(line: 115, column: 3, scope: !89)
!91 = !DILocation(line: 116, column: 3, scope: !89)
!92 = !DILocation(line: 118, column: 10, scope: !14)
!93 = !DILocation(line: 118, column: 2, scope: !14)
!94 = !DILocation(line: 119, column: 1, scope: !14)
!95 = !DILocalVariable(name: "res", arg: 1, scope: !39, file: !1, line: 122, type: !17)
!96 = !DILocation(line: 122, column: 76, scope: !39)
!97 = !DILocalVariable(name: "fmt", arg: 2, scope: !39, file: !1, line: 123, type: !38)
!98 = !DILocation(line: 123, column: 9, scope: !39)
!99 = !DILocalVariable(name: "fmtbase", scope: !39, file: !1, line: 125, type: !38)
!100 = !DILocation(line: 125, column: 6, scope: !39)
!101 = !DILocation(line: 125, column: 16, scope: !39)
!102 = !DILocation(line: 125, column: 20, scope: !39)
!103 = !DILocation(line: 127, column: 10, scope: !39)
!104 = !DILocation(line: 127, column: 2, scope: !39)
!105 = !DILocation(line: 131, column: 3, scope: !106)
!106 = distinct !DILexicalBlock(scope: !39, file: !1, line: 127, column: 19)
!107 = !DILocation(line: 131, column: 8, scope: !106)
!108 = !DILocation(line: 131, column: 17, scope: !106)
!109 = !DILocation(line: 132, column: 3, scope: !106)
!110 = !DILocation(line: 134, column: 11, scope: !106)
!111 = !DILocation(line: 134, column: 3, scope: !106)
!112 = !DILocation(line: 137, column: 4, scope: !113)
!113 = distinct !DILexicalBlock(scope: !106, file: !1, line: 134, column: 16)
!114 = !DILocation(line: 137, column: 9, scope: !113)
!115 = !DILocation(line: 137, column: 18, scope: !113)
!116 = !DILocation(line: 138, column: 4, scope: !113)
!117 = !DILocation(line: 140, column: 4, scope: !113)
!118 = !DILocation(line: 140, column: 9, scope: !113)
!119 = !DILocation(line: 140, column: 18, scope: !113)
!120 = !DILocation(line: 141, column: 4, scope: !113)
!121 = !DILocation(line: 143, column: 3, scope: !106)
!122 = !DILocation(line: 145, column: 3, scope: !106)
!123 = !DILocation(line: 145, column: 8, scope: !106)
!124 = !DILocation(line: 145, column: 17, scope: !106)
!125 = !DILocation(line: 146, column: 3, scope: !106)
!126 = !DILocation(line: 151, column: 3, scope: !106)
!127 = !DILocation(line: 151, column: 8, scope: !106)
!128 = !DILocation(line: 151, column: 17, scope: !106)
!129 = !DILocation(line: 152, column: 3, scope: !106)
!130 = !DILocation(line: 154, column: 3, scope: !106)
!131 = !DILocation(line: 154, column: 8, scope: !106)
!132 = !DILocation(line: 154, column: 17, scope: !106)
!133 = !DILocation(line: 155, column: 3, scope: !106)
!134 = !DILocation(line: 157, column: 1, scope: !39)
!135 = !DILocalVariable(name: "res", arg: 1, scope: !42, file: !1, line: 160, type: !17)
!136 = !DILocation(line: 160, column: 68, scope: !42)
!137 = !DILocalVariable(name: "le", scope: !42, file: !1, line: 162, type: !22)
!138 = !DILocation(line: 162, column: 22, scope: !42)
!139 = !DILocation(line: 164, column: 6, scope: !140)
!140 = distinct !DILexicalBlock(scope: !42, file: !1, line: 164, column: 6)
!141 = !DILocation(line: 164, column: 10, scope: !140)
!142 = !DILocation(line: 164, column: 6, scope: !42)
!143 = !DILocation(line: 165, column: 3, scope: !140)
!144 = !DILocation(line: 167, column: 2, scope: !42)
!145 = !DILocation(line: 167, column: 26, scope: !146)
!146 = !DILexicalBlockFile(scope: !42, file: !1, discriminator: 1)
!147 = !DILocation(line: 167, column: 15, scope: !146)
!148 = !DILocation(line: 167, column: 13, scope: !146)
!149 = !DILocation(line: 167, column: 48, scope: !146)
!150 = !DILocation(line: 167, column: 2, scope: !146)
!151 = !DILocation(line: 168, column: 22, scope: !42)
!152 = !DILocation(line: 168, column: 26, scope: !42)
!153 = !DILocation(line: 168, column: 3, scope: !42)
!154 = !DILocation(line: 167, column: 2, scope: !155)
!155 = !DILexicalBlockFile(scope: !42, file: !1, discriminator: 2)
!156 = !DILocation(line: 169, column: 7, scope: !42)
!157 = !DILocation(line: 169, column: 12, scope: !42)
!158 = !DILocation(line: 169, column: 2, scope: !42)
!159 = !DILocation(line: 170, column: 7, scope: !42)
!160 = !DILocation(line: 170, column: 2, scope: !42)
!161 = !DILocation(line: 171, column: 1, scope: !42)
!162 = !DILocation(line: 171, column: 1, scope: !146)
!163 = !DILocalVariable(name: "res", arg: 1, scope: !56, file: !1, line: 313, type: !17)
!164 = !DILocation(line: 313, column: 47, scope: !56)
!165 = !DILocalVariable(name: "mode", arg: 2, scope: !56, file: !1, line: 313, type: !38)
!166 = !DILocation(line: 313, column: 56, scope: !56)
!167 = !DILocalVariable(name: "le", scope: !56, file: !1, line: 315, type: !22)
!168 = !DILocation(line: 315, column: 22, scope: !56)
!169 = !DILocalVariable(name: "bucket", scope: !56, file: !1, line: 316, type: !10)
!170 = !DILocation(line: 316, column: 12, scope: !56)
!171 = !DILocation(line: 319, column: 6, scope: !172)
!172 = distinct !DILexicalBlock(scope: !56, file: !1, line: 319, column: 6)
!173 = !DILocation(line: 319, column: 11, scope: !172)
!174 = !DILocation(line: 319, column: 17, scope: !172)
!175 = !DILocation(line: 319, column: 6, scope: !56)
!176 = !DILocation(line: 320, column: 22, scope: !177)
!177 = distinct !DILexicalBlock(scope: !172, file: !1, line: 319, column: 26)
!178 = !DILocation(line: 320, column: 27, scope: !177)
!179 = !DILocation(line: 320, column: 34, scope: !177)
!180 = !DILocation(line: 320, column: 3, scope: !177)
!181 = !DILocation(line: 321, column: 22, scope: !177)
!182 = !DILocation(line: 321, column: 27, scope: !177)
!183 = !DILocation(line: 321, column: 34, scope: !177)
!184 = !DILocation(line: 321, column: 3, scope: !177)
!185 = !DILocation(line: 322, column: 8, scope: !177)
!186 = !DILocation(line: 322, column: 13, scope: !177)
!187 = !DILocation(line: 322, column: 3, scope: !177)
!188 = !DILocation(line: 323, column: 3, scope: !177)
!189 = !DILocation(line: 323, column: 8, scope: !177)
!190 = !DILocation(line: 323, column: 14, scope: !177)
!191 = !DILocation(line: 324, column: 2, scope: !177)
!192 = !DILocation(line: 327, column: 14, scope: !193)
!193 = distinct !DILexicalBlock(scope: !56, file: !1, line: 327, column: 2)
!194 = !DILocation(line: 327, column: 7, scope: !193)
!195 = !DILocation(line: 327, column: 19, scope: !196)
!196 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 1)
!197 = distinct !DILexicalBlock(scope: !193, file: !1, line: 327, column: 2)
!198 = !DILocation(line: 327, column: 28, scope: !196)
!199 = !DILocation(line: 327, column: 33, scope: !196)
!200 = !DILocation(line: 327, column: 26, scope: !196)
!201 = !DILocation(line: 327, column: 2, scope: !196)
!202 = !DILocation(line: 328, column: 26, scope: !203)
!203 = distinct !DILexicalBlock(scope: !204, file: !1, line: 328, column: 3)
!204 = distinct !DILexicalBlock(scope: !197, file: !1, line: 327, column: 59)
!205 = !DILocation(line: 328, column: 13, scope: !203)
!206 = !DILocation(line: 328, column: 18, scope: !203)
!207 = !DILocation(line: 328, column: 11, scope: !203)
!208 = !DILocation(line: 328, column: 8, scope: !203)
!209 = !DILocation(line: 328, column: 35, scope: !210)
!210 = !DILexicalBlockFile(scope: !211, file: !1, discriminator: 1)
!211 = distinct !DILexicalBlock(scope: !203, file: !1, line: 328, column: 3)
!212 = !DILocation(line: 328, column: 38, scope: !210)
!213 = !DILocation(line: 328, column: 3, scope: !210)
!214 = !DILocation(line: 329, column: 8, scope: !215)
!215 = distinct !DILexicalBlock(scope: !216, file: !1, line: 329, column: 8)
!216 = distinct !DILexicalBlock(scope: !211, file: !1, line: 328, column: 62)
!217 = !DILocation(line: 329, column: 12, scope: !215)
!218 = !DILocation(line: 329, column: 18, scope: !215)
!219 = !DILocation(line: 329, column: 26, scope: !215)
!220 = !DILocation(line: 330, column: 9, scope: !215)
!221 = !DILocation(line: 330, column: 14, scope: !215)
!222 = !DILocation(line: 330, column: 37, scope: !215)
!223 = !DILocation(line: 329, column: 8, scope: !224)
!224 = !DILexicalBlockFile(scope: !216, file: !1, discriminator: 1)
!225 = !DILocation(line: 331, column: 5, scope: !215)
!226 = !DILocation(line: 332, column: 8, scope: !227)
!227 = distinct !DILexicalBlock(scope: !216, file: !1, line: 332, column: 8)
!228 = !DILocation(line: 332, column: 12, scope: !227)
!229 = !DILocation(line: 332, column: 18, scope: !227)
!230 = !DILocation(line: 332, column: 26, scope: !227)
!231 = !DILocation(line: 333, column: 9, scope: !227)
!232 = !DILocation(line: 333, column: 14, scope: !227)
!233 = !DILocation(line: 333, column: 36, scope: !227)
!234 = !DILocation(line: 332, column: 8, scope: !224)
!235 = !DILocation(line: 334, column: 5, scope: !227)
!236 = !DILocation(line: 336, column: 8, scope: !237)
!237 = distinct !DILexicalBlock(scope: !216, file: !1, line: 336, column: 8)
!238 = !DILocation(line: 336, column: 12, scope: !237)
!239 = !DILocation(line: 336, column: 17, scope: !237)
!240 = !DILocation(line: 336, column: 8, scope: !216)
!241 = !DILocation(line: 337, column: 26, scope: !237)
!242 = !DILocation(line: 337, column: 30, scope: !237)
!243 = !DILocation(line: 337, column: 5, scope: !237)
!244 = !DILocation(line: 337, column: 9, scope: !237)
!245 = !DILocation(line: 337, column: 15, scope: !237)
!246 = !DILocation(line: 337, column: 24, scope: !237)
!247 = !DILocation(line: 338, column: 8, scope: !248)
!248 = distinct !DILexicalBlock(scope: !216, file: !1, line: 338, column: 8)
!249 = !DILocation(line: 338, column: 12, scope: !248)
!250 = !DILocation(line: 338, column: 21, scope: !248)
!251 = !DILocation(line: 338, column: 8, scope: !216)
!252 = !DILocation(line: 339, column: 26, scope: !248)
!253 = !DILocation(line: 339, column: 30, scope: !248)
!254 = !DILocation(line: 339, column: 5, scope: !248)
!255 = !DILocation(line: 339, column: 9, scope: !248)
!256 = !DILocation(line: 339, column: 19, scope: !248)
!257 = !DILocation(line: 339, column: 24, scope: !248)
!258 = !DILocation(line: 341, column: 28, scope: !248)
!259 = !DILocation(line: 341, column: 32, scope: !248)
!260 = !DILocation(line: 341, column: 18, scope: !248)
!261 = !DILocation(line: 341, column: 5, scope: !248)
!262 = !DILocation(line: 341, column: 10, scope: !248)
!263 = !DILocation(line: 341, column: 26, scope: !248)
!264 = !DILocation(line: 342, column: 4, scope: !216)
!265 = !DILocation(line: 342, column: 9, scope: !216)
!266 = !DILocation(line: 342, column: 23, scope: !216)
!267 = !DILocation(line: 344, column: 17, scope: !216)
!268 = !DILocation(line: 344, column: 4, scope: !216)
!269 = !DILocation(line: 344, column: 9, scope: !216)
!270 = !DILocation(line: 344, column: 15, scope: !216)
!271 = !DILocation(line: 345, column: 12, scope: !216)
!272 = !DILocation(line: 345, column: 4, scope: !216)
!273 = !DILocation(line: 328, column: 52, scope: !274)
!274 = !DILexicalBlockFile(scope: !211, file: !1, discriminator: 2)
!275 = !DILocation(line: 328, column: 56, scope: !274)
!276 = !DILocation(line: 328, column: 50, scope: !274)
!277 = !DILocation(line: 328, column: 3, scope: !274)
!278 = !DILocation(line: 347, column: 2, scope: !204)
!279 = !DILocation(line: 327, column: 55, scope: !280)
!280 = !DILexicalBlockFile(scope: !197, file: !1, discriminator: 2)
!281 = !DILocation(line: 327, column: 2, scope: !280)
!282 = !DILocation(line: 348, column: 2, scope: !56)
!283 = !DILocation(line: 349, column: 1, scope: !56)
!284 = !DILocalVariable(name: "res", arg: 1, scope: !45, file: !1, line: 174, type: !17)
!285 = !DILocation(line: 174, column: 58, scope: !45)
!286 = !DILocalVariable(name: "e", arg: 2, scope: !45, file: !1, line: 175, type: !48)
!287 = !DILocation(line: 175, column: 28, scope: !45)
!288 = !DILocalVariable(name: "f", arg: 3, scope: !45, file: !1, line: 175, type: !48)
!289 = !DILocation(line: 175, column: 54, scope: !45)
!290 = !DILocalVariable(name: "le", scope: !45, file: !1, line: 177, type: !22)
!291 = !DILocation(line: 177, column: 22, scope: !45)
!292 = !DILocalVariable(name: "t", scope: !45, file: !1, line: 178, type: !28)
!293 = !DILocation(line: 178, column: 24, scope: !45)
!294 = !DILocation(line: 180, column: 3, scope: !45)
!295 = !DILocation(line: 180, column: 5, scope: !45)
!296 = !DILocation(line: 182, column: 7, scope: !297)
!297 = distinct !DILexicalBlock(scope: !45, file: !1, line: 182, column: 6)
!298 = !DILocation(line: 182, column: 6, scope: !297)
!299 = !DILocation(line: 182, column: 9, scope: !297)
!300 = !DILocation(line: 182, column: 6, scope: !45)
!301 = !DILocation(line: 183, column: 19, scope: !302)
!302 = distinct !DILexicalBlock(scope: !297, file: !1, line: 182, column: 18)
!303 = !DILocation(line: 183, column: 8, scope: !302)
!304 = !DILocation(line: 183, column: 6, scope: !302)
!305 = !DILocation(line: 184, column: 7, scope: !306)
!306 = distinct !DILexicalBlock(scope: !302, file: !1, line: 184, column: 7)
!307 = !DILocation(line: 184, column: 10, scope: !306)
!308 = !DILocation(line: 184, column: 7, scope: !302)
!309 = !DILocation(line: 185, column: 9, scope: !310)
!310 = distinct !DILexicalBlock(scope: !306, file: !1, line: 184, column: 19)
!311 = !DILocation(line: 185, column: 13, scope: !310)
!312 = !DILocation(line: 185, column: 5, scope: !310)
!313 = !DILocation(line: 185, column: 7, scope: !310)
!314 = !DILocation(line: 186, column: 4, scope: !310)
!315 = !DILocation(line: 186, column: 8, scope: !310)
!316 = !DILocation(line: 186, column: 14, scope: !310)
!317 = !DILocation(line: 187, column: 3, scope: !310)
!318 = !DILocation(line: 188, column: 3, scope: !302)
!319 = !DILocation(line: 192, column: 27, scope: !320)
!320 = distinct !DILexicalBlock(scope: !45, file: !1, line: 192, column: 6)
!321 = !DILocation(line: 192, column: 26, scope: !320)
!322 = !DILocation(line: 192, column: 6, scope: !320)
!323 = !DILocation(line: 192, column: 30, scope: !320)
!324 = !DILocation(line: 192, column: 6, scope: !45)
!325 = !DILocation(line: 193, column: 3, scope: !320)
!326 = !DILocation(line: 195, column: 30, scope: !327)
!327 = distinct !DILexicalBlock(scope: !45, file: !1, line: 195, column: 6)
!328 = !DILocation(line: 195, column: 29, scope: !327)
!329 = !DILocation(line: 195, column: 6, scope: !327)
!330 = !DILocation(line: 195, column: 33, scope: !327)
!331 = !DILocation(line: 196, column: 6, scope: !327)
!332 = !DILocation(line: 196, column: 33, scope: !333)
!333 = !DILexicalBlockFile(scope: !327, file: !1, discriminator: 1)
!334 = !DILocation(line: 196, column: 32, scope: !333)
!335 = !DILocation(line: 196, column: 9, scope: !333)
!336 = !DILocation(line: 196, column: 36, scope: !333)
!337 = !DILocation(line: 197, column: 6, scope: !327)
!338 = !DILocation(line: 197, column: 33, scope: !333)
!339 = !DILocation(line: 197, column: 32, scope: !333)
!340 = !DILocation(line: 197, column: 9, scope: !333)
!341 = !DILocation(line: 197, column: 36, scope: !333)
!342 = !DILocation(line: 195, column: 6, scope: !343)
!343 = !DILexicalBlockFile(scope: !45, file: !1, discriminator: 1)
!344 = !DILocation(line: 198, column: 3, scope: !327)
!345 = !DILocation(line: 200, column: 10, scope: !45)
!346 = !DILocation(line: 200, column: 15, scope: !45)
!347 = !DILocation(line: 200, column: 2, scope: !45)
!348 = !DILocation(line: 202, column: 19, scope: !349)
!349 = distinct !DILexicalBlock(scope: !45, file: !1, line: 200, column: 25)
!350 = !DILocation(line: 202, column: 25, scope: !349)
!351 = !DILocation(line: 202, column: 24, scope: !349)
!352 = !DILocation(line: 202, column: 8, scope: !349)
!353 = !DILocation(line: 202, column: 6, scope: !349)
!354 = !DILocation(line: 203, column: 7, scope: !355)
!355 = distinct !DILexicalBlock(scope: !349, file: !1, line: 203, column: 7)
!356 = !DILocation(line: 203, column: 10, scope: !355)
!357 = !DILocation(line: 203, column: 7, scope: !349)
!358 = !DILocation(line: 204, column: 30, scope: !359)
!359 = distinct !DILexicalBlock(scope: !355, file: !1, line: 203, column: 19)
!360 = !DILocation(line: 204, column: 29, scope: !359)
!361 = !DILocation(line: 204, column: 4, scope: !359)
!362 = !DILocation(line: 205, column: 33, scope: !359)
!363 = !DILocation(line: 205, column: 32, scope: !359)
!364 = !DILocation(line: 206, column: 31, scope: !359)
!365 = !DILocation(line: 206, column: 35, scope: !359)
!366 = !DILocation(line: 206, column: 8, scope: !359)
!367 = !DILocation(line: 205, column: 4, scope: !359)
!368 = !DILocation(line: 207, column: 3, scope: !359)
!369 = !DILocation(line: 208, column: 17, scope: !355)
!370 = !DILocation(line: 208, column: 23, scope: !355)
!371 = !DILocation(line: 208, column: 22, scope: !355)
!372 = !DILocation(line: 208, column: 4, scope: !355)
!373 = !DILocation(line: 209, column: 3, scope: !349)
!374 = !DILocation(line: 211, column: 19, scope: !349)
!375 = !DILocation(line: 211, column: 25, scope: !349)
!376 = !DILocation(line: 211, column: 24, scope: !349)
!377 = !DILocation(line: 211, column: 8, scope: !349)
!378 = !DILocation(line: 211, column: 6, scope: !349)
!379 = !DILocation(line: 212, column: 7, scope: !380)
!380 = distinct !DILexicalBlock(scope: !349, file: !1, line: 212, column: 7)
!381 = !DILocation(line: 212, column: 10, scope: !380)
!382 = !DILocation(line: 212, column: 7, scope: !349)
!383 = !DILocation(line: 213, column: 33, scope: !384)
!384 = distinct !DILexicalBlock(scope: !380, file: !1, line: 212, column: 19)
!385 = !DILocation(line: 213, column: 32, scope: !384)
!386 = !DILocation(line: 214, column: 31, scope: !384)
!387 = !DILocation(line: 214, column: 35, scope: !384)
!388 = !DILocation(line: 214, column: 8, scope: !384)
!389 = !DILocation(line: 213, column: 4, scope: !384)
!390 = !DILocation(line: 215, column: 3, scope: !384)
!391 = !DILocation(line: 216, column: 17, scope: !380)
!392 = !DILocation(line: 216, column: 23, scope: !380)
!393 = !DILocation(line: 216, column: 22, scope: !380)
!394 = !DILocation(line: 216, column: 4, scope: !380)
!395 = !DILocation(line: 217, column: 3, scope: !349)
!396 = !DILocation(line: 220, column: 3, scope: !349)
!397 = !DILocation(line: 222, column: 19, scope: !349)
!398 = !DILocation(line: 222, column: 25, scope: !349)
!399 = !DILocation(line: 222, column: 24, scope: !349)
!400 = !DILocation(line: 222, column: 8, scope: !349)
!401 = !DILocation(line: 222, column: 6, scope: !349)
!402 = !DILocation(line: 223, column: 7, scope: !403)
!403 = distinct !DILexicalBlock(scope: !349, file: !1, line: 223, column: 7)
!404 = !DILocation(line: 223, column: 10, scope: !403)
!405 = !DILocation(line: 223, column: 7, scope: !349)
!406 = !DILocation(line: 228, column: 9, scope: !407)
!407 = distinct !DILexicalBlock(scope: !403, file: !1, line: 223, column: 19)
!408 = !DILocation(line: 228, column: 8, scope: !407)
!409 = !DILocation(line: 228, column: 6, scope: !407)
!410 = !DILocation(line: 229, column: 9, scope: !407)
!411 = !DILocation(line: 229, column: 13, scope: !407)
!412 = !DILocation(line: 229, column: 5, scope: !407)
!413 = !DILocation(line: 229, column: 7, scope: !407)
!414 = !DILocation(line: 230, column: 16, scope: !407)
!415 = !DILocation(line: 230, column: 4, scope: !407)
!416 = !DILocation(line: 230, column: 8, scope: !407)
!417 = !DILocation(line: 230, column: 14, scope: !407)
!418 = !DILocation(line: 232, column: 30, scope: !407)
!419 = !DILocation(line: 232, column: 29, scope: !407)
!420 = !DILocation(line: 232, column: 4, scope: !407)
!421 = !DILocation(line: 233, column: 33, scope: !407)
!422 = !DILocation(line: 233, column: 32, scope: !407)
!423 = !DILocation(line: 234, column: 31, scope: !407)
!424 = !DILocation(line: 234, column: 35, scope: !407)
!425 = !DILocation(line: 234, column: 8, scope: !407)
!426 = !DILocation(line: 233, column: 4, scope: !407)
!427 = !DILocation(line: 237, column: 8, scope: !428)
!428 = distinct !DILexicalBlock(scope: !407, file: !1, line: 237, column: 8)
!429 = !DILocation(line: 237, column: 12, scope: !428)
!430 = !DILocation(line: 237, column: 18, scope: !428)
!431 = !DILocation(line: 237, column: 8, scope: !407)
!432 = !DILocation(line: 238, column: 10, scope: !433)
!433 = distinct !DILexicalBlock(scope: !428, file: !1, line: 237, column: 24)
!434 = !DILocation(line: 238, column: 14, scope: !433)
!435 = !DILocation(line: 238, column: 6, scope: !433)
!436 = !DILocation(line: 238, column: 8, scope: !433)
!437 = !DILocation(line: 239, column: 5, scope: !433)
!438 = !DILocation(line: 239, column: 9, scope: !433)
!439 = !DILocation(line: 239, column: 15, scope: !433)
!440 = !DILocation(line: 240, column: 4, scope: !433)
!441 = !DILocation(line: 241, column: 3, scope: !407)
!442 = !DILocation(line: 246, column: 22, scope: !443)
!443 = distinct !DILexicalBlock(scope: !403, file: !1, line: 241, column: 10)
!444 = !DILocation(line: 246, column: 28, scope: !443)
!445 = !DILocation(line: 246, column: 27, scope: !443)
!446 = !DILocation(line: 246, column: 9, scope: !443)
!447 = !DILocation(line: 246, column: 7, scope: !443)
!448 = !DILocation(line: 247, column: 8, scope: !449)
!449 = distinct !DILexicalBlock(scope: !443, file: !1, line: 247, column: 8)
!450 = !DILocation(line: 247, column: 11, scope: !449)
!451 = !DILocation(line: 247, column: 8, scope: !443)
!452 = !DILocation(line: 249, column: 5, scope: !449)
!453 = !DILocation(line: 250, column: 17, scope: !443)
!454 = !DILocation(line: 250, column: 16, scope: !443)
!455 = !DILocation(line: 250, column: 4, scope: !443)
!456 = !DILocation(line: 250, column: 8, scope: !443)
!457 = !DILocation(line: 250, column: 14, scope: !443)
!458 = !DILocation(line: 251, column: 5, scope: !443)
!459 = !DILocation(line: 251, column: 7, scope: !443)
!460 = !DILocation(line: 253, column: 3, scope: !349)
!461 = !DILocation(line: 255, column: 3, scope: !349)
!462 = !DILocation(line: 257, column: 2, scope: !45)
!463 = !DILocation(line: 258, column: 1, scope: !45)
!464 = !DILocalVariable(name: "res", arg: 1, scope: !53, file: !1, line: 261, type: !17)
!465 = !DILocation(line: 261, column: 47, scope: !53)
!466 = !DILocalVariable(name: "entry", arg: 2, scope: !53, file: !1, line: 262, type: !28)
!467 = !DILocation(line: 262, column: 27, scope: !53)
!468 = !DILocalVariable(name: "le", scope: !53, file: !1, line: 264, type: !22)
!469 = !DILocation(line: 264, column: 22, scope: !53)
!470 = !DILocalVariable(name: "hash", scope: !53, file: !1, line: 265, type: !10)
!471 = !DILocation(line: 265, column: 12, scope: !53)
!472 = !DILocalVariable(name: "bucket", scope: !53, file: !1, line: 265, type: !10)
!473 = !DILocation(line: 265, column: 18, scope: !53)
!474 = !DILocalVariable(name: "dev", scope: !53, file: !1, line: 266, type: !475)
!475 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !6, line: 44, baseType: !476)
!476 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !8, line: 124, baseType: !12)
!477 = !DILocation(line: 266, column: 11, scope: !53)
!478 = !DILocalVariable(name: "ino", scope: !53, file: !1, line: 267, type: !479)
!479 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !480, line: 40, baseType: !481)
!480 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!481 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!482 = !DILocation(line: 267, column: 13, scope: !53)
!483 = !DILocation(line: 270, column: 6, scope: !484)
!484 = distinct !DILexicalBlock(scope: !53, file: !1, line: 270, column: 6)
!485 = !DILocation(line: 270, column: 11, scope: !484)
!486 = !DILocation(line: 270, column: 17, scope: !484)
!487 = !DILocation(line: 270, column: 6, scope: !53)
!488 = !DILocation(line: 271, column: 22, scope: !489)
!489 = distinct !DILexicalBlock(scope: !484, file: !1, line: 270, column: 26)
!490 = !DILocation(line: 271, column: 27, scope: !489)
!491 = !DILocation(line: 271, column: 34, scope: !489)
!492 = !DILocation(line: 271, column: 3, scope: !489)
!493 = !DILocation(line: 272, column: 22, scope: !489)
!494 = !DILocation(line: 272, column: 27, scope: !489)
!495 = !DILocation(line: 272, column: 34, scope: !489)
!496 = !DILocation(line: 272, column: 3, scope: !489)
!497 = !DILocation(line: 273, column: 8, scope: !489)
!498 = !DILocation(line: 273, column: 13, scope: !489)
!499 = !DILocation(line: 273, column: 3, scope: !489)
!500 = !DILocation(line: 274, column: 3, scope: !489)
!501 = !DILocation(line: 274, column: 8, scope: !489)
!502 = !DILocation(line: 274, column: 14, scope: !489)
!503 = !DILocation(line: 275, column: 2, scope: !489)
!504 = !DILocation(line: 277, column: 26, scope: !53)
!505 = !DILocation(line: 277, column: 8, scope: !53)
!506 = !DILocation(line: 277, column: 6, scope: !53)
!507 = !DILocation(line: 278, column: 28, scope: !53)
!508 = !DILocation(line: 278, column: 8, scope: !53)
!509 = !DILocation(line: 278, column: 6, scope: !53)
!510 = !DILocation(line: 279, column: 18, scope: !53)
!511 = !DILocation(line: 279, column: 24, scope: !53)
!512 = !DILocation(line: 279, column: 22, scope: !53)
!513 = !DILocation(line: 279, column: 7, scope: !53)
!514 = !DILocation(line: 282, column: 11, scope: !53)
!515 = !DILocation(line: 282, column: 19, scope: !53)
!516 = !DILocation(line: 282, column: 24, scope: !53)
!517 = !DILocation(line: 282, column: 39, scope: !53)
!518 = !DILocation(line: 282, column: 16, scope: !53)
!519 = !DILocation(line: 282, column: 9, scope: !53)
!520 = !DILocation(line: 283, column: 25, scope: !521)
!521 = distinct !DILexicalBlock(scope: !53, file: !1, line: 283, column: 2)
!522 = !DILocation(line: 283, column: 12, scope: !521)
!523 = !DILocation(line: 283, column: 17, scope: !521)
!524 = !DILocation(line: 283, column: 10, scope: !521)
!525 = !DILocation(line: 283, column: 7, scope: !521)
!526 = !DILocation(line: 283, column: 34, scope: !527)
!527 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 1)
!528 = distinct !DILexicalBlock(scope: !521, file: !1, line: 283, column: 2)
!529 = !DILocation(line: 283, column: 37, scope: !527)
!530 = !DILocation(line: 283, column: 2, scope: !527)
!531 = !DILocation(line: 284, column: 7, scope: !532)
!532 = distinct !DILexicalBlock(scope: !533, file: !1, line: 284, column: 7)
!533 = distinct !DILexicalBlock(scope: !528, file: !1, line: 283, column: 61)
!534 = !DILocation(line: 284, column: 11, scope: !532)
!535 = !DILocation(line: 284, column: 19, scope: !532)
!536 = !DILocation(line: 284, column: 16, scope: !532)
!537 = !DILocation(line: 285, column: 7, scope: !532)
!538 = !DILocation(line: 285, column: 10, scope: !539)
!539 = !DILexicalBlockFile(scope: !532, file: !1, discriminator: 1)
!540 = !DILocation(line: 285, column: 35, scope: !539)
!541 = !DILocation(line: 285, column: 39, scope: !539)
!542 = !DILocation(line: 285, column: 17, scope: !539)
!543 = !DILocation(line: 285, column: 14, scope: !539)
!544 = !DILocation(line: 286, column: 7, scope: !532)
!545 = !DILocation(line: 286, column: 10, scope: !539)
!546 = !DILocation(line: 286, column: 37, scope: !539)
!547 = !DILocation(line: 286, column: 41, scope: !539)
!548 = !DILocation(line: 286, column: 17, scope: !539)
!549 = !DILocation(line: 286, column: 14, scope: !539)
!550 = !DILocation(line: 284, column: 7, scope: !551)
!551 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 1)
!552 = !DILocation(line: 293, column: 6, scope: !553)
!553 = distinct !DILexicalBlock(scope: !532, file: !1, line: 286, column: 53)
!554 = !DILocation(line: 293, column: 10, scope: !553)
!555 = !DILocation(line: 293, column: 4, scope: !553)
!556 = !DILocation(line: 294, column: 8, scope: !557)
!557 = distinct !DILexicalBlock(scope: !553, file: !1, line: 294, column: 8)
!558 = !DILocation(line: 294, column: 12, scope: !557)
!559 = !DILocation(line: 294, column: 18, scope: !557)
!560 = !DILocation(line: 294, column: 8, scope: !553)
!561 = !DILocation(line: 295, column: 13, scope: !557)
!562 = !DILocation(line: 295, column: 5, scope: !557)
!563 = !DILocation(line: 297, column: 8, scope: !564)
!564 = distinct !DILexicalBlock(scope: !553, file: !1, line: 297, column: 8)
!565 = !DILocation(line: 297, column: 12, scope: !564)
!566 = !DILocation(line: 297, column: 21, scope: !564)
!567 = !DILocation(line: 297, column: 8, scope: !553)
!568 = !DILocation(line: 298, column: 26, scope: !564)
!569 = !DILocation(line: 298, column: 30, scope: !564)
!570 = !DILocation(line: 298, column: 5, scope: !564)
!571 = !DILocation(line: 298, column: 9, scope: !564)
!572 = !DILocation(line: 298, column: 19, scope: !564)
!573 = !DILocation(line: 298, column: 24, scope: !564)
!574 = !DILocation(line: 299, column: 8, scope: !575)
!575 = distinct !DILexicalBlock(scope: !553, file: !1, line: 299, column: 8)
!576 = !DILocation(line: 299, column: 12, scope: !575)
!577 = !DILocation(line: 299, column: 17, scope: !575)
!578 = !DILocation(line: 299, column: 8, scope: !553)
!579 = !DILocation(line: 300, column: 26, scope: !575)
!580 = !DILocation(line: 300, column: 30, scope: !575)
!581 = !DILocation(line: 300, column: 5, scope: !575)
!582 = !DILocation(line: 300, column: 9, scope: !575)
!583 = !DILocation(line: 300, column: 15, scope: !575)
!584 = !DILocation(line: 300, column: 24, scope: !575)
!585 = !DILocation(line: 301, column: 21, scope: !586)
!586 = distinct !DILexicalBlock(scope: !553, file: !1, line: 301, column: 8)
!587 = !DILocation(line: 301, column: 8, scope: !586)
!588 = !DILocation(line: 301, column: 13, scope: !586)
!589 = !DILocation(line: 301, column: 32, scope: !586)
!590 = !DILocation(line: 301, column: 29, scope: !586)
!591 = !DILocation(line: 301, column: 8, scope: !553)
!592 = !DILocation(line: 302, column: 28, scope: !586)
!593 = !DILocation(line: 302, column: 32, scope: !586)
!594 = !DILocation(line: 302, column: 18, scope: !586)
!595 = !DILocation(line: 302, column: 5, scope: !586)
!596 = !DILocation(line: 302, column: 10, scope: !586)
!597 = !DILocation(line: 302, column: 26, scope: !586)
!598 = !DILocation(line: 303, column: 4, scope: !553)
!599 = !DILocation(line: 303, column: 9, scope: !553)
!600 = !DILocation(line: 303, column: 23, scope: !553)
!601 = !DILocation(line: 305, column: 17, scope: !553)
!602 = !DILocation(line: 305, column: 4, scope: !553)
!603 = !DILocation(line: 305, column: 9, scope: !553)
!604 = !DILocation(line: 305, column: 15, scope: !553)
!605 = !DILocation(line: 306, column: 12, scope: !553)
!606 = !DILocation(line: 306, column: 4, scope: !553)
!607 = !DILocation(line: 308, column: 2, scope: !533)
!608 = !DILocation(line: 283, column: 51, scope: !609)
!609 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 2)
!610 = !DILocation(line: 283, column: 55, scope: !609)
!611 = !DILocation(line: 283, column: 49, scope: !609)
!612 = !DILocation(line: 283, column: 2, scope: !609)
!613 = !DILocation(line: 309, column: 2, scope: !53)
!614 = !DILocation(line: 310, column: 1, scope: !53)
!615 = !DILocalVariable(name: "res", arg: 1, scope: !59, file: !1, line: 352, type: !17)
!616 = !DILocation(line: 352, column: 49, scope: !59)
!617 = !DILocalVariable(name: "entry", arg: 2, scope: !59, file: !1, line: 353, type: !28)
!618 = !DILocation(line: 353, column: 27, scope: !59)
!619 = !DILocalVariable(name: "le", scope: !59, file: !1, line: 355, type: !22)
!620 = !DILocation(line: 355, column: 22, scope: !59)
!621 = !DILocalVariable(name: "hash", scope: !59, file: !1, line: 356, type: !10)
!622 = !DILocation(line: 356, column: 9, scope: !59)
!623 = !DILocalVariable(name: "bucket", scope: !59, file: !1, line: 356, type: !10)
!624 = !DILocation(line: 356, column: 15, scope: !59)
!625 = !DILocation(line: 359, column: 7, scope: !59)
!626 = !DILocation(line: 359, column: 5, scope: !59)
!627 = !DILocation(line: 360, column: 6, scope: !628)
!628 = distinct !DILexicalBlock(scope: !59, file: !1, line: 360, column: 6)
!629 = !DILocation(line: 360, column: 9, scope: !628)
!630 = !DILocation(line: 360, column: 6, scope: !59)
!631 = !DILocation(line: 361, column: 3, scope: !628)
!632 = !DILocation(line: 362, column: 38, scope: !59)
!633 = !DILocation(line: 362, column: 18, scope: !59)
!634 = !DILocation(line: 362, column: 2, scope: !59)
!635 = !DILocation(line: 362, column: 6, scope: !59)
!636 = !DILocation(line: 362, column: 16, scope: !59)
!637 = !DILocation(line: 365, column: 6, scope: !638)
!638 = distinct !DILexicalBlock(scope: !59, file: !1, line: 365, column: 6)
!639 = !DILocation(line: 365, column: 11, scope: !638)
!640 = !DILocation(line: 365, column: 28, scope: !638)
!641 = !DILocation(line: 365, column: 33, scope: !638)
!642 = !DILocation(line: 365, column: 48, scope: !638)
!643 = !DILocation(line: 365, column: 26, scope: !638)
!644 = !DILocation(line: 365, column: 6, scope: !59)
!645 = !DILocation(line: 366, column: 13, scope: !638)
!646 = !DILocation(line: 366, column: 3, scope: !638)
!647 = !DILocation(line: 368, column: 36, scope: !59)
!648 = !DILocation(line: 368, column: 18, scope: !59)
!649 = !DILocation(line: 368, column: 65, scope: !59)
!650 = !DILocation(line: 368, column: 45, scope: !651)
!651 = !DILexicalBlockFile(scope: !59, file: !1, discriminator: 1)
!652 = !DILocation(line: 368, column: 43, scope: !59)
!653 = !DILocation(line: 368, column: 7, scope: !59)
!654 = !DILocation(line: 369, column: 11, scope: !59)
!655 = !DILocation(line: 369, column: 19, scope: !59)
!656 = !DILocation(line: 369, column: 24, scope: !59)
!657 = !DILocation(line: 369, column: 39, scope: !59)
!658 = !DILocation(line: 369, column: 16, scope: !59)
!659 = !DILocation(line: 369, column: 9, scope: !59)
!660 = !DILocation(line: 372, column: 19, scope: !661)
!661 = distinct !DILexicalBlock(scope: !59, file: !1, line: 372, column: 6)
!662 = !DILocation(line: 372, column: 6, scope: !661)
!663 = !DILocation(line: 372, column: 11, scope: !661)
!664 = !DILocation(line: 372, column: 27, scope: !661)
!665 = !DILocation(line: 372, column: 6, scope: !59)
!666 = !DILocation(line: 373, column: 36, scope: !661)
!667 = !DILocation(line: 373, column: 16, scope: !661)
!668 = !DILocation(line: 373, column: 3, scope: !661)
!669 = !DILocation(line: 373, column: 8, scope: !661)
!670 = !DILocation(line: 373, column: 25, scope: !661)
!671 = !DILocation(line: 373, column: 34, scope: !661)
!672 = !DILocation(line: 374, column: 2, scope: !59)
!673 = !DILocation(line: 374, column: 7, scope: !59)
!674 = !DILocation(line: 374, column: 21, scope: !59)
!675 = !DILocation(line: 375, column: 26, scope: !59)
!676 = !DILocation(line: 375, column: 13, scope: !59)
!677 = !DILocation(line: 375, column: 18, scope: !59)
!678 = !DILocation(line: 375, column: 2, scope: !59)
!679 = !DILocation(line: 375, column: 6, scope: !59)
!680 = !DILocation(line: 375, column: 11, scope: !59)
!681 = !DILocation(line: 376, column: 2, scope: !59)
!682 = !DILocation(line: 376, column: 6, scope: !59)
!683 = !DILocation(line: 376, column: 15, scope: !59)
!684 = !DILocation(line: 377, column: 25, scope: !59)
!685 = !DILocation(line: 377, column: 15, scope: !59)
!686 = !DILocation(line: 377, column: 2, scope: !59)
!687 = !DILocation(line: 377, column: 7, scope: !59)
!688 = !DILocation(line: 377, column: 23, scope: !59)
!689 = !DILocation(line: 378, column: 13, scope: !59)
!690 = !DILocation(line: 378, column: 2, scope: !59)
!691 = !DILocation(line: 378, column: 6, scope: !59)
!692 = !DILocation(line: 378, column: 11, scope: !59)
!693 = !DILocation(line: 379, column: 34, scope: !59)
!694 = !DILocation(line: 379, column: 14, scope: !59)
!695 = !DILocation(line: 379, column: 41, scope: !59)
!696 = !DILocation(line: 379, column: 2, scope: !59)
!697 = !DILocation(line: 379, column: 6, scope: !59)
!698 = !DILocation(line: 379, column: 12, scope: !59)
!699 = !DILocation(line: 380, column: 10, scope: !59)
!700 = !DILocation(line: 380, column: 2, scope: !59)
!701 = !DILocation(line: 381, column: 1, scope: !59)
!702 = !DILocalVariable(name: "res", arg: 1, scope: !49, file: !1, line: 421, type: !17)
!703 = !DILocation(line: 421, column: 64, scope: !49)
!704 = !DILocalVariable(name: "links", arg: 2, scope: !49, file: !1, line: 422, type: !52)
!705 = !DILocation(line: 422, column: 19, scope: !49)
!706 = !DILocalVariable(name: "e", scope: !49, file: !1, line: 424, type: !28)
!707 = !DILocation(line: 424, column: 24, scope: !49)
!708 = !DILocalVariable(name: "le", scope: !49, file: !1, line: 425, type: !22)
!709 = !DILocation(line: 425, column: 22, scope: !49)
!710 = !DILocation(line: 428, column: 6, scope: !711)
!711 = distinct !DILexicalBlock(scope: !49, file: !1, line: 428, column: 6)
!712 = !DILocation(line: 428, column: 11, scope: !711)
!713 = !DILocation(line: 428, column: 17, scope: !711)
!714 = !DILocation(line: 428, column: 6, scope: !49)
!715 = !DILocation(line: 429, column: 22, scope: !716)
!716 = distinct !DILexicalBlock(scope: !711, file: !1, line: 428, column: 26)
!717 = !DILocation(line: 429, column: 27, scope: !716)
!718 = !DILocation(line: 429, column: 34, scope: !716)
!719 = !DILocation(line: 429, column: 3, scope: !716)
!720 = !DILocation(line: 430, column: 22, scope: !716)
!721 = !DILocation(line: 430, column: 27, scope: !716)
!722 = !DILocation(line: 430, column: 34, scope: !716)
!723 = !DILocation(line: 430, column: 3, scope: !716)
!724 = !DILocation(line: 431, column: 8, scope: !716)
!725 = !DILocation(line: 431, column: 13, scope: !716)
!726 = !DILocation(line: 431, column: 3, scope: !716)
!727 = !DILocation(line: 432, column: 3, scope: !716)
!728 = !DILocation(line: 432, column: 8, scope: !716)
!729 = !DILocation(line: 432, column: 14, scope: !716)
!730 = !DILocation(line: 433, column: 2, scope: !716)
!731 = !DILocation(line: 435, column: 18, scope: !49)
!732 = !DILocation(line: 435, column: 7, scope: !49)
!733 = !DILocation(line: 435, column: 5, scope: !49)
!734 = !DILocation(line: 436, column: 6, scope: !735)
!735 = distinct !DILexicalBlock(scope: !49, file: !1, line: 436, column: 6)
!736 = !DILocation(line: 436, column: 9, scope: !735)
!737 = !DILocation(line: 436, column: 6, scope: !49)
!738 = !DILocation(line: 437, column: 7, scope: !739)
!739 = distinct !DILexicalBlock(scope: !735, file: !1, line: 436, column: 18)
!740 = !DILocation(line: 437, column: 11, scope: !739)
!741 = !DILocation(line: 437, column: 5, scope: !739)
!742 = !DILocation(line: 438, column: 7, scope: !743)
!743 = distinct !DILexicalBlock(scope: !739, file: !1, line: 438, column: 7)
!744 = !DILocation(line: 438, column: 13, scope: !743)
!745 = !DILocation(line: 438, column: 7, scope: !739)
!746 = !DILocation(line: 439, column: 13, scope: !743)
!747 = !DILocation(line: 439, column: 17, scope: !743)
!748 = !DILocation(line: 439, column: 5, scope: !743)
!749 = !DILocation(line: 439, column: 11, scope: !743)
!750 = !DILocation(line: 439, column: 4, scope: !743)
!751 = !DILocation(line: 440, column: 3, scope: !739)
!752 = !DILocation(line: 440, column: 7, scope: !739)
!753 = !DILocation(line: 440, column: 17, scope: !739)
!754 = !DILocation(line: 441, column: 2, scope: !739)
!755 = !DILocation(line: 442, column: 5, scope: !756)
!756 = distinct !DILexicalBlock(scope: !735, file: !1, line: 441, column: 9)
!757 = !DILocation(line: 443, column: 7, scope: !758)
!758 = distinct !DILexicalBlock(scope: !756, file: !1, line: 443, column: 7)
!759 = !DILocation(line: 443, column: 13, scope: !758)
!760 = !DILocation(line: 443, column: 7, scope: !756)
!761 = !DILocation(line: 444, column: 5, scope: !758)
!762 = !DILocation(line: 444, column: 11, scope: !758)
!763 = !DILocation(line: 444, column: 4, scope: !758)
!764 = !DILocation(line: 446, column: 10, scope: !49)
!765 = !DILocation(line: 446, column: 2, scope: !49)
!766 = !DILocalVariable(name: "res", arg: 1, scope: !60, file: !1, line: 384, type: !17)
!767 = !DILocation(line: 384, column: 46, scope: !60)
!768 = !DILocalVariable(name: "le", scope: !60, file: !1, line: 386, type: !22)
!769 = !DILocation(line: 386, column: 22, scope: !60)
!770 = !DILocalVariable(name: "new_buckets", scope: !60, file: !1, line: 386, type: !21)
!771 = !DILocation(line: 386, column: 28, scope: !60)
!772 = !DILocalVariable(name: "new_size", scope: !60, file: !1, line: 387, type: !10)
!773 = !DILocation(line: 387, column: 9, scope: !60)
!774 = !DILocalVariable(name: "i", scope: !60, file: !1, line: 388, type: !10)
!775 = !DILocation(line: 388, column: 9, scope: !60)
!776 = !DILocalVariable(name: "bucket", scope: !60, file: !1, line: 388, type: !10)
!777 = !DILocation(line: 388, column: 12, scope: !60)
!778 = !DILocation(line: 391, column: 13, scope: !60)
!779 = !DILocation(line: 391, column: 18, scope: !60)
!780 = !DILocation(line: 391, column: 33, scope: !60)
!781 = !DILocation(line: 391, column: 11, scope: !60)
!782 = !DILocation(line: 392, column: 6, scope: !783)
!783 = distinct !DILexicalBlock(scope: !60, file: !1, line: 392, column: 6)
!784 = !DILocation(line: 392, column: 17, scope: !783)
!785 = !DILocation(line: 392, column: 22, scope: !783)
!786 = !DILocation(line: 392, column: 15, scope: !783)
!787 = !DILocation(line: 392, column: 6, scope: !60)
!788 = !DILocation(line: 393, column: 3, scope: !783)
!789 = !DILocation(line: 394, column: 23, scope: !60)
!790 = !DILocation(line: 394, column: 16, scope: !60)
!791 = !DILocation(line: 394, column: 14, scope: !60)
!792 = !DILocation(line: 396, column: 6, scope: !793)
!793 = distinct !DILexicalBlock(scope: !60, file: !1, line: 396, column: 6)
!794 = !DILocation(line: 396, column: 18, scope: !793)
!795 = !DILocation(line: 396, column: 6, scope: !60)
!796 = !DILocation(line: 397, column: 3, scope: !793)
!797 = !DILocation(line: 399, column: 9, scope: !798)
!798 = distinct !DILexicalBlock(scope: !60, file: !1, line: 399, column: 2)
!799 = !DILocation(line: 399, column: 7, scope: !798)
!800 = !DILocation(line: 399, column: 14, scope: !801)
!801 = !DILexicalBlockFile(scope: !802, file: !1, discriminator: 1)
!802 = distinct !DILexicalBlock(scope: !798, file: !1, line: 399, column: 2)
!803 = !DILocation(line: 399, column: 18, scope: !801)
!804 = !DILocation(line: 399, column: 23, scope: !801)
!805 = !DILocation(line: 399, column: 16, scope: !801)
!806 = !DILocation(line: 399, column: 2, scope: !801)
!807 = !DILocation(line: 400, column: 3, scope: !808)
!808 = distinct !DILexicalBlock(scope: !802, file: !1, line: 399, column: 44)
!809 = !DILocation(line: 400, column: 23, scope: !810)
!810 = !DILexicalBlockFile(scope: !808, file: !1, discriminator: 1)
!811 = !DILocation(line: 400, column: 10, scope: !810)
!812 = !DILocation(line: 400, column: 15, scope: !810)
!813 = !DILocation(line: 400, column: 26, scope: !810)
!814 = !DILocation(line: 400, column: 3, scope: !810)
!815 = !DILocation(line: 402, column: 22, scope: !816)
!816 = distinct !DILexicalBlock(scope: !808, file: !1, line: 400, column: 35)
!817 = !DILocation(line: 402, column: 9, scope: !816)
!818 = !DILocation(line: 402, column: 14, scope: !816)
!819 = !DILocation(line: 402, column: 7, scope: !816)
!820 = !DILocation(line: 403, column: 22, scope: !816)
!821 = !DILocation(line: 403, column: 26, scope: !816)
!822 = !DILocation(line: 403, column: 17, scope: !816)
!823 = !DILocation(line: 403, column: 4, scope: !816)
!824 = !DILocation(line: 403, column: 9, scope: !816)
!825 = !DILocation(line: 403, column: 20, scope: !816)
!826 = !DILocation(line: 406, column: 13, scope: !816)
!827 = !DILocation(line: 406, column: 17, scope: !816)
!828 = !DILocation(line: 406, column: 25, scope: !816)
!829 = !DILocation(line: 406, column: 34, scope: !816)
!830 = !DILocation(line: 406, column: 22, scope: !816)
!831 = !DILocation(line: 406, column: 11, scope: !816)
!832 = !DILocation(line: 408, column: 20, scope: !833)
!833 = distinct !DILexicalBlock(scope: !816, file: !1, line: 408, column: 8)
!834 = !DILocation(line: 408, column: 8, scope: !833)
!835 = !DILocation(line: 408, column: 28, scope: !833)
!836 = !DILocation(line: 408, column: 8, scope: !816)
!837 = !DILocation(line: 409, column: 37, scope: !833)
!838 = !DILocation(line: 409, column: 17, scope: !833)
!839 = !DILocation(line: 409, column: 5, scope: !833)
!840 = !DILocation(line: 409, column: 26, scope: !833)
!841 = !DILocation(line: 409, column: 35, scope: !833)
!842 = !DILocation(line: 410, column: 27, scope: !816)
!843 = !DILocation(line: 410, column: 15, scope: !816)
!844 = !DILocation(line: 410, column: 4, scope: !816)
!845 = !DILocation(line: 410, column: 8, scope: !816)
!846 = !DILocation(line: 410, column: 13, scope: !816)
!847 = !DILocation(line: 411, column: 4, scope: !816)
!848 = !DILocation(line: 411, column: 8, scope: !816)
!849 = !DILocation(line: 411, column: 17, scope: !816)
!850 = !DILocation(line: 412, column: 26, scope: !816)
!851 = !DILocation(line: 412, column: 16, scope: !816)
!852 = !DILocation(line: 412, column: 4, scope: !816)
!853 = !DILocation(line: 412, column: 24, scope: !816)
!854 = !DILocation(line: 400, column: 3, scope: !855)
!855 = !DILexicalBlockFile(scope: !808, file: !1, discriminator: 2)
!856 = !DILocation(line: 414, column: 2, scope: !808)
!857 = !DILocation(line: 399, column: 40, scope: !858)
!858 = !DILexicalBlockFile(scope: !802, file: !1, discriminator: 2)
!859 = !DILocation(line: 399, column: 2, scope: !858)
!860 = !DILocation(line: 415, column: 7, scope: !60)
!861 = !DILocation(line: 415, column: 12, scope: !60)
!862 = !DILocation(line: 415, column: 2, scope: !60)
!863 = !DILocation(line: 416, column: 17, scope: !60)
!864 = !DILocation(line: 416, column: 2, scope: !60)
!865 = !DILocation(line: 416, column: 7, scope: !60)
!866 = !DILocation(line: 416, column: 15, scope: !60)
!867 = !DILocation(line: 417, column: 24, scope: !60)
!868 = !DILocation(line: 417, column: 2, scope: !60)
!869 = !DILocation(line: 417, column: 7, scope: !60)
!870 = !DILocation(line: 417, column: 22, scope: !60)
!871 = !DILocation(line: 418, column: 1, scope: !60)
!872 = !DILocation(line: 418, column: 1, scope: !873)
!873 = !DILexicalBlockFile(scope: !60, file: !1, discriminator: 1)
