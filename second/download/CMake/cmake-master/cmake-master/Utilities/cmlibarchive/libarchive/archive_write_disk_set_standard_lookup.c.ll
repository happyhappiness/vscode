; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_disk_set_standard_lookup.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.bucket = type { i8*, i32, i32 }
%struct.group = type { i8*, i8*, i32, i8** }
%struct.passwd = type { i8*, i8*, i32, i32, i8*, i8*, i8* }

; Function Attrs: nounwind uwtable
define i32 @archive_write_disk_set_standard_lookup(%struct.archive* %a) #0 !dbg !24 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %ucache = alloca %struct.bucket*, align 8
  %gcache = alloca %struct.bucket*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !136, metadata !137), !dbg !138
  call void @llvm.dbg.declare(metadata %struct.bucket** %ucache, metadata !139, metadata !137), !dbg !140
  %call = call noalias i8* @calloc(i64 127, i64 16) #5, !dbg !141
  %0 = bitcast i8* %call to %struct.bucket*, !dbg !141
  store %struct.bucket* %0, %struct.bucket** %ucache, align 8, !dbg !140
  call void @llvm.dbg.declare(metadata %struct.bucket** %gcache, metadata !142, metadata !137), !dbg !143
  %call1 = call noalias i8* @calloc(i64 127, i64 16) #5, !dbg !144
  %1 = bitcast i8* %call1 to %struct.bucket*, !dbg !144
  store %struct.bucket* %1, %struct.bucket** %gcache, align 8, !dbg !143
  %2 = load %struct.bucket*, %struct.bucket** %ucache, align 8, !dbg !145
  %cmp = icmp eq %struct.bucket* %2, null, !dbg !147
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !148

lor.lhs.false:                                    ; preds = %entry
  %3 = load %struct.bucket*, %struct.bucket** %gcache, align 8, !dbg !149
  %cmp2 = icmp eq %struct.bucket* %3, null, !dbg !151
  br i1 %cmp2, label %if.then, label %if.end, !dbg !152

if.then:                                          ; preds = %lor.lhs.false, %entry
  %4 = load %struct.bucket*, %struct.bucket** %ucache, align 8, !dbg !153
  %5 = bitcast %struct.bucket* %4 to i8*, !dbg !153
  call void @free(i8* %5) #5, !dbg !155
  %6 = load %struct.bucket*, %struct.bucket** %gcache, align 8, !dbg !156
  %7 = bitcast %struct.bucket* %6 to i8*, !dbg !156
  call void @free(i8* %7) #5, !dbg !157
  store i32 -30, i32* %retval, align 4, !dbg !158
  br label %return, !dbg !158

if.end:                                           ; preds = %lor.lhs.false
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !159
  %9 = load %struct.bucket*, %struct.bucket** %gcache, align 8, !dbg !160
  %10 = bitcast %struct.bucket* %9 to i8*, !dbg !160
  %call3 = call i32 @archive_write_disk_set_group_lookup(%struct.archive* %8, i8* %10, i64 (i8*, i8*, i64)* @lookup_gid, void (i8*)* @cleanup), !dbg !161
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !162
  %12 = load %struct.bucket*, %struct.bucket** %ucache, align 8, !dbg !163
  %13 = bitcast %struct.bucket* %12 to i8*, !dbg !163
  %call4 = call i32 @archive_write_disk_set_user_lookup(%struct.archive* %11, i8* %13, i64 (i8*, i8*, i64)* @lookup_uid, void (i8*)* @cleanup), !dbg !164
  store i32 0, i32* %retval, align 4, !dbg !165
  br label %return, !dbg !165

return:                                           ; preds = %if.end, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !166
  ret i32 %14, !dbg !166
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #2

declare i32 @archive_write_disk_set_group_lookup(%struct.archive*, i8*, i64 (i8*, i8*, i64)*, void (i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i64 @lookup_gid(i8* %private_data, i8* %gname, i64 %gid) #0 !dbg !120 {
entry:
  %retval = alloca i64, align 8
  %private_data.addr = alloca i8*, align 8
  %gname.addr = alloca i8*, align 8
  %gid.addr = alloca i64, align 8
  %h = alloca i32, align 4
  %b = alloca %struct.bucket*, align 8
  %gcache = alloca %struct.bucket*, align 8
  %_buffer = alloca [128 x i8], align 16
  %bufsize = alloca i64, align 8
  %buffer = alloca i8*, align 8
  %allocated = alloca i8*, align 8
  %grent = alloca %struct.group, align 8
  %result = alloca %struct.group*, align 8
  %r = alloca i32, align 4
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !167, metadata !137), !dbg !168
  store i8* %gname, i8** %gname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %gname.addr, metadata !169, metadata !137), !dbg !170
  store i64 %gid, i64* %gid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %gid.addr, metadata !171, metadata !137), !dbg !172
  call void @llvm.dbg.declare(metadata i32* %h, metadata !173, metadata !137), !dbg !174
  call void @llvm.dbg.declare(metadata %struct.bucket** %b, metadata !175, metadata !137), !dbg !176
  call void @llvm.dbg.declare(metadata %struct.bucket** %gcache, metadata !177, metadata !137), !dbg !178
  %0 = load i8*, i8** %private_data.addr, align 8, !dbg !179
  %1 = bitcast i8* %0 to %struct.bucket*, !dbg !180
  store %struct.bucket* %1, %struct.bucket** %gcache, align 8, !dbg !178
  %2 = load i8*, i8** %gname.addr, align 8, !dbg !181
  %cmp = icmp eq i8* %2, null, !dbg !183
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !184

lor.lhs.false:                                    ; preds = %entry
  %3 = load i8*, i8** %gname.addr, align 8, !dbg !185
  %4 = load i8, i8* %3, align 1, !dbg !187
  %conv = sext i8 %4 to i32, !dbg !187
  %cmp1 = icmp eq i32 %conv, 0, !dbg !188
  br i1 %cmp1, label %if.then, label %if.end, !dbg !189

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load i64, i64* %gid.addr, align 8, !dbg !190
  store i64 %5, i64* %retval, align 8, !dbg !191
  br label %return, !dbg !191

if.end:                                           ; preds = %lor.lhs.false
  %6 = load i8*, i8** %gname.addr, align 8, !dbg !192
  %call = call i32 @hash(i8* %6), !dbg !193
  store i32 %call, i32* %h, align 4, !dbg !194
  %7 = load i32, i32* %h, align 4, !dbg !195
  %conv3 = sext i32 %7 to i64, !dbg !195
  %rem = urem i64 %conv3, 127, !dbg !196
  %8 = load %struct.bucket*, %struct.bucket** %gcache, align 8, !dbg !197
  %arrayidx = getelementptr inbounds %struct.bucket, %struct.bucket* %8, i64 %rem, !dbg !197
  store %struct.bucket* %arrayidx, %struct.bucket** %b, align 8, !dbg !198
  %9 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !199
  %name = getelementptr inbounds %struct.bucket, %struct.bucket* %9, i32 0, i32 0, !dbg !201
  %10 = load i8*, i8** %name, align 8, !dbg !201
  %cmp4 = icmp ne i8* %10, null, !dbg !202
  br i1 %cmp4, label %land.lhs.true, label %if.end15, !dbg !203

land.lhs.true:                                    ; preds = %if.end
  %11 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !204
  %hash = getelementptr inbounds %struct.bucket, %struct.bucket* %11, i32 0, i32 1, !dbg !206
  %12 = load i32, i32* %hash, align 8, !dbg !206
  %13 = load i32, i32* %h, align 4, !dbg !207
  %cmp6 = icmp eq i32 %12, %13, !dbg !208
  br i1 %cmp6, label %land.lhs.true8, label %if.end15, !dbg !209

land.lhs.true8:                                   ; preds = %land.lhs.true
  %14 = load i8*, i8** %gname.addr, align 8, !dbg !210
  %15 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !212
  %name9 = getelementptr inbounds %struct.bucket, %struct.bucket* %15, i32 0, i32 0, !dbg !213
  %16 = load i8*, i8** %name9, align 8, !dbg !213
  %call10 = call i32 @strcmp(i8* %14, i8* %16) #6, !dbg !214
  %cmp11 = icmp eq i32 %call10, 0, !dbg !215
  br i1 %cmp11, label %if.then13, label %if.end15, !dbg !216

if.then13:                                        ; preds = %land.lhs.true8
  %17 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !217
  %id = getelementptr inbounds %struct.bucket, %struct.bucket* %17, i32 0, i32 2, !dbg !218
  %18 = load i32, i32* %id, align 4, !dbg !218
  %conv14 = zext i32 %18 to i64, !dbg !219
  store i64 %conv14, i64* %retval, align 8, !dbg !220
  br label %return, !dbg !220

if.end15:                                         ; preds = %land.lhs.true8, %land.lhs.true, %if.end
  %19 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !221
  %name16 = getelementptr inbounds %struct.bucket, %struct.bucket* %19, i32 0, i32 0, !dbg !223
  %20 = load i8*, i8** %name16, align 8, !dbg !223
  %cmp17 = icmp ne i8* %20, null, !dbg !224
  br i1 %cmp17, label %if.then19, label %if.end21, !dbg !225

if.then19:                                        ; preds = %if.end15
  %21 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !226
  %name20 = getelementptr inbounds %struct.bucket, %struct.bucket* %21, i32 0, i32 0, !dbg !227
  %22 = load i8*, i8** %name20, align 8, !dbg !227
  call void @free(i8* %22) #5, !dbg !228
  br label %if.end21, !dbg !228

if.end21:                                         ; preds = %if.then19, %if.end15
  %23 = load i8*, i8** %gname.addr, align 8, !dbg !229
  %call22 = call noalias i8* @strdup(i8* %23) #5, !dbg !230
  %24 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !231
  %name23 = getelementptr inbounds %struct.bucket, %struct.bucket* %24, i32 0, i32 0, !dbg !232
  store i8* %call22, i8** %name23, align 8, !dbg !233
  %25 = load i32, i32* %h, align 4, !dbg !234
  %26 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !235
  %hash24 = getelementptr inbounds %struct.bucket, %struct.bucket* %26, i32 0, i32 1, !dbg !236
  store i32 %25, i32* %hash24, align 8, !dbg !237
  call void @llvm.dbg.declare(metadata [128 x i8]* %_buffer, metadata !238, metadata !137), !dbg !243
  call void @llvm.dbg.declare(metadata i64* %bufsize, metadata !244, metadata !137), !dbg !245
  store i64 128, i64* %bufsize, align 8, !dbg !245
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !246, metadata !137), !dbg !247
  %arraydecay = getelementptr inbounds [128 x i8], [128 x i8]* %_buffer, i32 0, i32 0, !dbg !248
  store i8* %arraydecay, i8** %buffer, align 8, !dbg !247
  call void @llvm.dbg.declare(metadata i8** %allocated, metadata !249, metadata !137), !dbg !250
  store i8* null, i8** %allocated, align 8, !dbg !250
  call void @llvm.dbg.declare(metadata %struct.group* %grent, metadata !251, metadata !137), !dbg !260
  call void @llvm.dbg.declare(metadata %struct.group** %result, metadata !261, metadata !137), !dbg !263
  call void @llvm.dbg.declare(metadata i32* %r, metadata !264, metadata !137), !dbg !265
  br label %for.cond, !dbg !266

for.cond:                                         ; preds = %if.end38, %if.end21
  store %struct.group* %grent, %struct.group** %result, align 8, !dbg !267
  %27 = load i8*, i8** %gname.addr, align 8, !dbg !271
  %28 = load i8*, i8** %buffer, align 8, !dbg !272
  %29 = load i64, i64* %bufsize, align 8, !dbg !273
  %call25 = call i32 @getgrnam_r(i8* %27, %struct.group* %grent, i8* %28, i64 %29, %struct.group** %result), !dbg !274
  store i32 %call25, i32* %r, align 4, !dbg !275
  %30 = load i32, i32* %r, align 4, !dbg !276
  %cmp26 = icmp eq i32 %30, 0, !dbg !278
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !279

if.then28:                                        ; preds = %for.cond
  br label %for.end, !dbg !280

if.end29:                                         ; preds = %for.cond
  %31 = load i32, i32* %r, align 4, !dbg !281
  %cmp30 = icmp ne i32 %31, 34, !dbg !283
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !284

if.then32:                                        ; preds = %if.end29
  br label %for.end, !dbg !285

if.end33:                                         ; preds = %if.end29
  %32 = load i64, i64* %bufsize, align 8, !dbg !286
  %mul = mul i64 %32, 2, !dbg !286
  store i64 %mul, i64* %bufsize, align 8, !dbg !286
  %33 = load i8*, i8** %allocated, align 8, !dbg !287
  call void @free(i8* %33) #5, !dbg !288
  %34 = load i64, i64* %bufsize, align 8, !dbg !289
  %call34 = call noalias i8* @malloc(i64 %34) #5, !dbg !290
  store i8* %call34, i8** %allocated, align 8, !dbg !291
  %35 = load i8*, i8** %allocated, align 8, !dbg !292
  %cmp35 = icmp eq i8* %35, null, !dbg !294
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !295

if.then37:                                        ; preds = %if.end33
  br label %for.end, !dbg !296

if.end38:                                         ; preds = %if.end33
  %36 = load i8*, i8** %allocated, align 8, !dbg !297
  store i8* %36, i8** %buffer, align 8, !dbg !298
  br label %for.cond, !dbg !299

for.end:                                          ; preds = %if.then37, %if.then32, %if.then28
  %37 = load %struct.group*, %struct.group** %result, align 8, !dbg !301
  %cmp39 = icmp ne %struct.group* %37, null, !dbg !303
  br i1 %cmp39, label %if.then41, label %if.end43, !dbg !304

if.then41:                                        ; preds = %for.end
  %38 = load %struct.group*, %struct.group** %result, align 8, !dbg !305
  %gr_gid = getelementptr inbounds %struct.group, %struct.group* %38, i32 0, i32 2, !dbg !306
  %39 = load i32, i32* %gr_gid, align 8, !dbg !306
  %conv42 = zext i32 %39 to i64, !dbg !305
  store i64 %conv42, i64* %gid.addr, align 8, !dbg !307
  br label %if.end43, !dbg !308

if.end43:                                         ; preds = %if.then41, %for.end
  %40 = load i8*, i8** %allocated, align 8, !dbg !309
  call void @free(i8* %40) #5, !dbg !310
  %41 = load i64, i64* %gid.addr, align 8, !dbg !311
  %conv44 = trunc i64 %41 to i32, !dbg !312
  %42 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !313
  %id45 = getelementptr inbounds %struct.bucket, %struct.bucket* %42, i32 0, i32 2, !dbg !314
  store i32 %conv44, i32* %id45, align 4, !dbg !315
  %43 = load i64, i64* %gid.addr, align 8, !dbg !316
  store i64 %43, i64* %retval, align 8, !dbg !317
  br label %return, !dbg !317

return:                                           ; preds = %if.end43, %if.then13, %if.then
  %44 = load i64, i64* %retval, align 8, !dbg !318
  ret i64 %44, !dbg !318
}

; Function Attrs: nounwind uwtable
define internal void @cleanup(i8* %private) #0 !dbg !127 {
entry:
  %private.addr = alloca i8*, align 8
  %i = alloca i64, align 8
  %cache = alloca %struct.bucket*, align 8
  store i8* %private, i8** %private.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private.addr, metadata !319, metadata !137), !dbg !320
  call void @llvm.dbg.declare(metadata i64* %i, metadata !321, metadata !137), !dbg !322
  call void @llvm.dbg.declare(metadata %struct.bucket** %cache, metadata !323, metadata !137), !dbg !324
  %0 = load i8*, i8** %private.addr, align 8, !dbg !325
  %1 = bitcast i8* %0 to %struct.bucket*, !dbg !326
  store %struct.bucket* %1, %struct.bucket** %cache, align 8, !dbg !324
  store i64 0, i64* %i, align 8, !dbg !327
  br label %for.cond, !dbg !329

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i64, i64* %i, align 8, !dbg !330
  %cmp = icmp ult i64 %2, 127, !dbg !333
  br i1 %cmp, label %for.body, label %for.end, !dbg !334

for.body:                                         ; preds = %for.cond
  %3 = load i64, i64* %i, align 8, !dbg !335
  %4 = load %struct.bucket*, %struct.bucket** %cache, align 8, !dbg !336
  %arrayidx = getelementptr inbounds %struct.bucket, %struct.bucket* %4, i64 %3, !dbg !336
  %name = getelementptr inbounds %struct.bucket, %struct.bucket* %arrayidx, i32 0, i32 0, !dbg !337
  %5 = load i8*, i8** %name, align 8, !dbg !337
  call void @free(i8* %5) #5, !dbg !338
  br label %for.inc, !dbg !338

for.inc:                                          ; preds = %for.body
  %6 = load i64, i64* %i, align 8, !dbg !339
  %inc = add i64 %6, 1, !dbg !339
  store i64 %inc, i64* %i, align 8, !dbg !339
  br label %for.cond, !dbg !341

for.end:                                          ; preds = %for.cond
  %7 = load %struct.bucket*, %struct.bucket** %cache, align 8, !dbg !342
  %8 = bitcast %struct.bucket* %7 to i8*, !dbg !342
  call void @free(i8* %8) #5, !dbg !343
  ret void, !dbg !344
}

declare i32 @archive_write_disk_set_user_lookup(%struct.archive*, i8*, i64 (i8*, i8*, i64)*, void (i8*)*) #3

; Function Attrs: nounwind uwtable
define internal i64 @lookup_uid(i8* %private_data, i8* %uname, i64 %uid) #0 !dbg !126 {
entry:
  %retval = alloca i64, align 8
  %private_data.addr = alloca i8*, align 8
  %uname.addr = alloca i8*, align 8
  %uid.addr = alloca i64, align 8
  %h = alloca i32, align 4
  %b = alloca %struct.bucket*, align 8
  %ucache = alloca %struct.bucket*, align 8
  %_buffer = alloca [128 x i8], align 16
  %bufsize = alloca i64, align 8
  %buffer = alloca i8*, align 8
  %allocated = alloca i8*, align 8
  %pwent = alloca %struct.passwd, align 8
  %result = alloca %struct.passwd*, align 8
  %r = alloca i32, align 4
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !345, metadata !137), !dbg !346
  store i8* %uname, i8** %uname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %uname.addr, metadata !347, metadata !137), !dbg !348
  store i64 %uid, i64* %uid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uid.addr, metadata !349, metadata !137), !dbg !350
  call void @llvm.dbg.declare(metadata i32* %h, metadata !351, metadata !137), !dbg !352
  call void @llvm.dbg.declare(metadata %struct.bucket** %b, metadata !353, metadata !137), !dbg !354
  call void @llvm.dbg.declare(metadata %struct.bucket** %ucache, metadata !355, metadata !137), !dbg !356
  %0 = load i8*, i8** %private_data.addr, align 8, !dbg !357
  %1 = bitcast i8* %0 to %struct.bucket*, !dbg !358
  store %struct.bucket* %1, %struct.bucket** %ucache, align 8, !dbg !356
  %2 = load i8*, i8** %uname.addr, align 8, !dbg !359
  %cmp = icmp eq i8* %2, null, !dbg !361
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !362

lor.lhs.false:                                    ; preds = %entry
  %3 = load i8*, i8** %uname.addr, align 8, !dbg !363
  %4 = load i8, i8* %3, align 1, !dbg !365
  %conv = sext i8 %4 to i32, !dbg !365
  %cmp1 = icmp eq i32 %conv, 0, !dbg !366
  br i1 %cmp1, label %if.then, label %if.end, !dbg !367

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load i64, i64* %uid.addr, align 8, !dbg !368
  store i64 %5, i64* %retval, align 8, !dbg !369
  br label %return, !dbg !369

if.end:                                           ; preds = %lor.lhs.false
  %6 = load i8*, i8** %uname.addr, align 8, !dbg !370
  %call = call i32 @hash(i8* %6), !dbg !371
  store i32 %call, i32* %h, align 4, !dbg !372
  %7 = load i32, i32* %h, align 4, !dbg !373
  %conv3 = sext i32 %7 to i64, !dbg !373
  %rem = urem i64 %conv3, 127, !dbg !374
  %8 = load %struct.bucket*, %struct.bucket** %ucache, align 8, !dbg !375
  %arrayidx = getelementptr inbounds %struct.bucket, %struct.bucket* %8, i64 %rem, !dbg !375
  store %struct.bucket* %arrayidx, %struct.bucket** %b, align 8, !dbg !376
  %9 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !377
  %name = getelementptr inbounds %struct.bucket, %struct.bucket* %9, i32 0, i32 0, !dbg !379
  %10 = load i8*, i8** %name, align 8, !dbg !379
  %cmp4 = icmp ne i8* %10, null, !dbg !380
  br i1 %cmp4, label %land.lhs.true, label %if.end15, !dbg !381

land.lhs.true:                                    ; preds = %if.end
  %11 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !382
  %hash = getelementptr inbounds %struct.bucket, %struct.bucket* %11, i32 0, i32 1, !dbg !384
  %12 = load i32, i32* %hash, align 8, !dbg !384
  %13 = load i32, i32* %h, align 4, !dbg !385
  %cmp6 = icmp eq i32 %12, %13, !dbg !386
  br i1 %cmp6, label %land.lhs.true8, label %if.end15, !dbg !387

land.lhs.true8:                                   ; preds = %land.lhs.true
  %14 = load i8*, i8** %uname.addr, align 8, !dbg !388
  %15 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !390
  %name9 = getelementptr inbounds %struct.bucket, %struct.bucket* %15, i32 0, i32 0, !dbg !391
  %16 = load i8*, i8** %name9, align 8, !dbg !391
  %call10 = call i32 @strcmp(i8* %14, i8* %16) #6, !dbg !392
  %cmp11 = icmp eq i32 %call10, 0, !dbg !393
  br i1 %cmp11, label %if.then13, label %if.end15, !dbg !394

if.then13:                                        ; preds = %land.lhs.true8
  %17 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !395
  %id = getelementptr inbounds %struct.bucket, %struct.bucket* %17, i32 0, i32 2, !dbg !396
  %18 = load i32, i32* %id, align 4, !dbg !396
  %conv14 = zext i32 %18 to i64, !dbg !397
  store i64 %conv14, i64* %retval, align 8, !dbg !398
  br label %return, !dbg !398

if.end15:                                         ; preds = %land.lhs.true8, %land.lhs.true, %if.end
  %19 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !399
  %name16 = getelementptr inbounds %struct.bucket, %struct.bucket* %19, i32 0, i32 0, !dbg !401
  %20 = load i8*, i8** %name16, align 8, !dbg !401
  %cmp17 = icmp ne i8* %20, null, !dbg !402
  br i1 %cmp17, label %if.then19, label %if.end21, !dbg !403

if.then19:                                        ; preds = %if.end15
  %21 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !404
  %name20 = getelementptr inbounds %struct.bucket, %struct.bucket* %21, i32 0, i32 0, !dbg !405
  %22 = load i8*, i8** %name20, align 8, !dbg !405
  call void @free(i8* %22) #5, !dbg !406
  br label %if.end21, !dbg !406

if.end21:                                         ; preds = %if.then19, %if.end15
  %23 = load i8*, i8** %uname.addr, align 8, !dbg !407
  %call22 = call noalias i8* @strdup(i8* %23) #5, !dbg !408
  %24 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !409
  %name23 = getelementptr inbounds %struct.bucket, %struct.bucket* %24, i32 0, i32 0, !dbg !410
  store i8* %call22, i8** %name23, align 8, !dbg !411
  %25 = load i32, i32* %h, align 4, !dbg !412
  %26 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !413
  %hash24 = getelementptr inbounds %struct.bucket, %struct.bucket* %26, i32 0, i32 1, !dbg !414
  store i32 %25, i32* %hash24, align 8, !dbg !415
  call void @llvm.dbg.declare(metadata [128 x i8]* %_buffer, metadata !416, metadata !137), !dbg !418
  call void @llvm.dbg.declare(metadata i64* %bufsize, metadata !419, metadata !137), !dbg !420
  store i64 128, i64* %bufsize, align 8, !dbg !420
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !421, metadata !137), !dbg !422
  %arraydecay = getelementptr inbounds [128 x i8], [128 x i8]* %_buffer, i32 0, i32 0, !dbg !423
  store i8* %arraydecay, i8** %buffer, align 8, !dbg !422
  call void @llvm.dbg.declare(metadata i8** %allocated, metadata !424, metadata !137), !dbg !425
  store i8* null, i8** %allocated, align 8, !dbg !425
  call void @llvm.dbg.declare(metadata %struct.passwd* %pwent, metadata !426, metadata !137), !dbg !437
  call void @llvm.dbg.declare(metadata %struct.passwd** %result, metadata !438, metadata !137), !dbg !440
  call void @llvm.dbg.declare(metadata i32* %r, metadata !441, metadata !137), !dbg !442
  br label %for.cond, !dbg !443

for.cond:                                         ; preds = %if.end38, %if.end21
  store %struct.passwd* %pwent, %struct.passwd** %result, align 8, !dbg !444
  %27 = load i8*, i8** %uname.addr, align 8, !dbg !448
  %28 = load i8*, i8** %buffer, align 8, !dbg !449
  %29 = load i64, i64* %bufsize, align 8, !dbg !450
  %call25 = call i32 @getpwnam_r(i8* %27, %struct.passwd* %pwent, i8* %28, i64 %29, %struct.passwd** %result), !dbg !451
  store i32 %call25, i32* %r, align 4, !dbg !452
  %30 = load i32, i32* %r, align 4, !dbg !453
  %cmp26 = icmp eq i32 %30, 0, !dbg !455
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !456

if.then28:                                        ; preds = %for.cond
  br label %for.end, !dbg !457

if.end29:                                         ; preds = %for.cond
  %31 = load i32, i32* %r, align 4, !dbg !458
  %cmp30 = icmp ne i32 %31, 34, !dbg !460
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !461

if.then32:                                        ; preds = %if.end29
  br label %for.end, !dbg !462

if.end33:                                         ; preds = %if.end29
  %32 = load i64, i64* %bufsize, align 8, !dbg !463
  %mul = mul i64 %32, 2, !dbg !463
  store i64 %mul, i64* %bufsize, align 8, !dbg !463
  %33 = load i8*, i8** %allocated, align 8, !dbg !464
  call void @free(i8* %33) #5, !dbg !465
  %34 = load i64, i64* %bufsize, align 8, !dbg !466
  %call34 = call noalias i8* @malloc(i64 %34) #5, !dbg !467
  store i8* %call34, i8** %allocated, align 8, !dbg !468
  %35 = load i8*, i8** %allocated, align 8, !dbg !469
  %cmp35 = icmp eq i8* %35, null, !dbg !471
  br i1 %cmp35, label %if.then37, label %if.end38, !dbg !472

if.then37:                                        ; preds = %if.end33
  br label %for.end, !dbg !473

if.end38:                                         ; preds = %if.end33
  %36 = load i8*, i8** %allocated, align 8, !dbg !474
  store i8* %36, i8** %buffer, align 8, !dbg !475
  br label %for.cond, !dbg !476

for.end:                                          ; preds = %if.then37, %if.then32, %if.then28
  %37 = load %struct.passwd*, %struct.passwd** %result, align 8, !dbg !478
  %cmp39 = icmp ne %struct.passwd* %37, null, !dbg !480
  br i1 %cmp39, label %if.then41, label %if.end43, !dbg !481

if.then41:                                        ; preds = %for.end
  %38 = load %struct.passwd*, %struct.passwd** %result, align 8, !dbg !482
  %pw_uid = getelementptr inbounds %struct.passwd, %struct.passwd* %38, i32 0, i32 2, !dbg !483
  %39 = load i32, i32* %pw_uid, align 8, !dbg !483
  %conv42 = zext i32 %39 to i64, !dbg !482
  store i64 %conv42, i64* %uid.addr, align 8, !dbg !484
  br label %if.end43, !dbg !485

if.end43:                                         ; preds = %if.then41, %for.end
  %40 = load i8*, i8** %allocated, align 8, !dbg !486
  call void @free(i8* %40) #5, !dbg !487
  %41 = load i64, i64* %uid.addr, align 8, !dbg !488
  %conv44 = trunc i64 %41 to i32, !dbg !489
  %42 = load %struct.bucket*, %struct.bucket** %b, align 8, !dbg !490
  %id45 = getelementptr inbounds %struct.bucket, %struct.bucket* %42, i32 0, i32 2, !dbg !491
  store i32 %conv44, i32* %id45, align 4, !dbg !492
  %43 = load i64, i64* %uid.addr, align 8, !dbg !493
  store i64 %43, i64* %retval, align 8, !dbg !494
  br label %return, !dbg !494

return:                                           ; preds = %if.end43, %if.then13, %if.then
  %44 = load i64, i64* %retval, align 8, !dbg !495
  ret i64 %44, !dbg !495
}

; Function Attrs: nounwind uwtable
define internal i32 @hash(i8* %p) #0 !dbg !123 {
entry:
  %p.addr = alloca i8*, align 8
  %g = alloca i32, align 4
  %h = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !496, metadata !137), !dbg !497
  call void @llvm.dbg.declare(metadata i32* %g, metadata !498, metadata !137), !dbg !499
  call void @llvm.dbg.declare(metadata i32* %h, metadata !500, metadata !137), !dbg !501
  store i32 0, i32* %h, align 4, !dbg !501
  br label %while.cond, !dbg !502

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i8*, i8** %p.addr, align 8, !dbg !503
  %1 = load i8, i8* %0, align 1, !dbg !505
  %conv = sext i8 %1 to i32, !dbg !505
  %cmp = icmp ne i32 %conv, 0, !dbg !506
  br i1 %cmp, label %while.body, label %while.end, !dbg !507

while.body:                                       ; preds = %while.cond
  %2 = load i32, i32* %h, align 4, !dbg !508
  %shl = shl i32 %2, 4, !dbg !510
  %3 = load i8*, i8** %p.addr, align 8, !dbg !511
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !511
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !511
  %4 = load i8, i8* %3, align 1, !dbg !512
  %conv2 = sext i8 %4 to i32, !dbg !512
  %add = add i32 %shl, %conv2, !dbg !513
  store i32 %add, i32* %h, align 4, !dbg !514
  %5 = load i32, i32* %h, align 4, !dbg !515
  %and = and i32 %5, -268435456, !dbg !517
  store i32 %and, i32* %g, align 4, !dbg !518
  %cmp3 = icmp ne i32 %and, 0, !dbg !519
  br i1 %cmp3, label %if.then, label %if.end, !dbg !520

if.then:                                          ; preds = %while.body
  %6 = load i32, i32* %g, align 4, !dbg !521
  %shr = lshr i32 %6, 24, !dbg !523
  %7 = load i32, i32* %h, align 4, !dbg !524
  %xor = xor i32 %7, %shr, !dbg !524
  store i32 %xor, i32* %h, align 4, !dbg !524
  %8 = load i32, i32* %h, align 4, !dbg !525
  %and5 = and i32 %8, 268435455, !dbg !525
  store i32 %and5, i32* %h, align 4, !dbg !525
  br label %if.end, !dbg !526

if.end:                                           ; preds = %if.then, %while.body
  br label %while.cond, !dbg !527

while.end:                                        ; preds = %while.cond
  %9 = load i32, i32* %h, align 4, !dbg !529
  ret i32 %9, !dbg !530
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #2

declare i32 @getgrnam_r(i8*, %struct.group*, i8*, i64, %struct.group**) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

declare i32 @getpwnam_r(i8*, %struct.passwd*, i8*, i64, %struct.passwd**) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!133, !134}
!llvm.ident = !{!135}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !23, globals: !130)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_disk_set_standard_lookup.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !19, !21}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "bucket", file: !1, line: 53, size: 128, align: 64, elements: !7)
!7 = !{!8, !11, !13}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !6, file: !1, line: 54, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !6, file: !1, line: 55, baseType: !12, size: 32, align: 32, offset: 64)
!12 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !6, file: !1, line: 56, baseType: !14, size: 32, align: 32, offset: 96)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "id_t", file: !15, line: 104, baseType: !16)
!15 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "__id_t", file: !17, line: 138, baseType: !18)
!17 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !15, line: 65, baseType: !20)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !17, line: 126, baseType: !18)
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !15, line: 80, baseType: !22)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !17, line: 125, baseType: !18)
!23 = !{!24, !120, !123, !126, !127}
!24 = distinct !DISubprogram(name: "archive_write_disk_set_standard_lookup", scope: !1, file: !1, line: 85, type: !25, isLocal: false, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!25 = !DISubroutineType(types: !26)
!26 = !{!12, !27}
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !29, line: 89, size: 1280, align: 64, elements: !30)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!30 = !{!31, !32, !33, !94, !95, !96, !97, !98, !99, !100, !101, !108, !109, !110, !111, !114, !115, !116, !117, !118, !119}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !28, file: !29, line: 96, baseType: !18, size: 32, align: 32)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !28, file: !29, line: 97, baseType: !18, size: 32, align: 32, offset: 32)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !28, file: !29, line: 103, baseType: !34, size: 64, align: 64, offset: 64)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !29, line: 63, size: 832, align: 64, elements: !36)
!36 = !{!37, !39, !40, !47, !48, !60, !66, !71, !72, !79, !80, !84, !88}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !35, file: !29, line: 64, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !35, file: !29, line: 65, baseType: !38, size: 64, align: 64, offset: 64)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !35, file: !29, line: 66, baseType: !41, size: 64, align: 64, offset: 128)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DISubroutineType(types: !43)
!43 = !{!12, !27, !44}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !46, line: 180, flags: DIFlagFwdDecl)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !35, file: !29, line: 68, baseType: !38, size: 64, align: 64, offset: 192)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !35, file: !29, line: 69, baseType: !49, size: 64, align: 64, offset: 256)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!52, !27, !55, !57}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !15, line: 109, baseType: !53)
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !17, line: 172, baseType: !54)
!54 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !58, line: 62, baseType: !59)
!58 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!59 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !35, file: !29, line: 71, baseType: !61, size: 64, align: 64, offset: 320)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!52, !27, !55, !57, !64}
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !65, line: 40, baseType: !54)
!65 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !35, file: !29, line: 74, baseType: !67, size: 64, align: 64, offset: 384)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!12, !27, !70}
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !35, file: !29, line: 76, baseType: !41, size: 64, align: 64, offset: 448)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !35, file: !29, line: 78, baseType: !73, size: 64, align: 64, offset: 512)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!12, !27, !76, !77, !78}
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !35, file: !29, line: 81, baseType: !38, size: 64, align: 64, offset: 576)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !35, file: !29, line: 82, baseType: !81, size: 64, align: 64, offset: 640)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{!64, !27, !12}
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !35, file: !29, line: 83, baseType: !85, size: 64, align: 64, offset: 704)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!12, !27, !12}
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !35, file: !29, line: 84, baseType: !89, size: 64, align: 64, offset: 768)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!92, !27, !12}
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !10)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !28, file: !29, line: 105, baseType: !12, size: 32, align: 32, offset: 128)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !28, file: !29, line: 106, baseType: !92, size: 64, align: 64, offset: 192)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !28, file: !29, line: 108, baseType: !12, size: 32, align: 32, offset: 256)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !28, file: !29, line: 109, baseType: !92, size: 64, align: 64, offset: 320)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !28, file: !29, line: 112, baseType: !12, size: 32, align: 32, offset: 384)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !28, file: !29, line: 114, baseType: !12, size: 32, align: 32, offset: 416)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !28, file: !29, line: 115, baseType: !92, size: 64, align: 64, offset: 448)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !28, file: !29, line: 116, baseType: !102, size: 192, align: 64, offset: 512)
!102 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !103, line: 58, size: 192, align: 64, elements: !104)
!103 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!104 = !{!105, !106, !107}
!105 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !102, file: !103, line: 59, baseType: !9, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !102, file: !103, line: 60, baseType: !57, size: 64, align: 64, offset: 64)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !102, file: !103, line: 61, baseType: !57, size: 64, align: 64, offset: 128)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !28, file: !29, line: 118, baseType: !9, size: 64, align: 64, offset: 704)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !28, file: !29, line: 119, baseType: !18, size: 32, align: 32, offset: 768)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !28, file: !29, line: 120, baseType: !18, size: 32, align: 32, offset: 800)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !28, file: !29, line: 121, baseType: !112, size: 64, align: 64, offset: 832)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !103, line: 70, flags: DIFlagFwdDecl)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !28, file: !29, line: 127, baseType: !92, size: 64, align: 64, offset: 896)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !28, file: !29, line: 128, baseType: !64, size: 64, align: 64, offset: 960)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !28, file: !29, line: 129, baseType: !64, size: 64, align: 64, offset: 1024)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !28, file: !29, line: 130, baseType: !57, size: 64, align: 64, offset: 1088)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !28, file: !29, line: 137, baseType: !10, size: 8, align: 8, offset: 1152)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !28, file: !29, line: 138, baseType: !57, size: 64, align: 64, offset: 1216)
!120 = distinct !DISubprogram(name: "lookup_gid", scope: !1, file: !1, line: 100, type: !121, isLocal: true, isDefinition: true, scopeLine: 101, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!121 = !DISubroutineType(types: !122)
!122 = !{!64, !4, !92, !64}
!123 = distinct !DISubprogram(name: "hash", scope: !1, file: !1, line: 252, type: !124, isLocal: true, isDefinition: true, scopeLine: 253, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!124 = !DISubroutineType(types: !125)
!125 = !{!18, !92}
!126 = distinct !DISubprogram(name: "lookup_uid", scope: !1, file: !1, line: 170, type: !121, isLocal: true, isDefinition: true, scopeLine: 171, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!127 = distinct !DISubprogram(name: "cleanup", scope: !1, file: !1, line: 240, type: !128, isLocal: true, isDefinition: true, scopeLine: 241, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!128 = !DISubroutineType(types: !129)
!129 = !{null, !4}
!130 = !{!131}
!131 = !DIGlobalVariable(name: "cache_size", scope: !0, file: !1, line: 59, type: !132, isLocal: true, isDefinition: true, variable: i64 127)
!132 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !57)
!133 = !{i32 2, !"Dwarf Version", i32 4}
!134 = !{i32 2, !"Debug Info Version", i32 3}
!135 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!136 = !DILocalVariable(name: "a", arg: 1, scope: !24, file: !1, line: 85, type: !27)
!137 = !DIExpression()
!138 = !DILocation(line: 85, column: 56, scope: !24)
!139 = !DILocalVariable(name: "ucache", scope: !24, file: !1, line: 87, type: !5)
!140 = !DILocation(line: 87, column: 17, scope: !24)
!141 = !DILocation(line: 87, column: 26, scope: !24)
!142 = !DILocalVariable(name: "gcache", scope: !24, file: !1, line: 88, type: !5)
!143 = !DILocation(line: 88, column: 17, scope: !24)
!144 = !DILocation(line: 88, column: 26, scope: !24)
!145 = !DILocation(line: 89, column: 6, scope: !146)
!146 = distinct !DILexicalBlock(scope: !24, file: !1, line: 89, column: 6)
!147 = !DILocation(line: 89, column: 13, scope: !146)
!148 = !DILocation(line: 89, column: 21, scope: !146)
!149 = !DILocation(line: 89, column: 24, scope: !150)
!150 = !DILexicalBlockFile(scope: !146, file: !1, discriminator: 1)
!151 = !DILocation(line: 89, column: 31, scope: !150)
!152 = !DILocation(line: 89, column: 6, scope: !150)
!153 = !DILocation(line: 90, column: 8, scope: !154)
!154 = distinct !DILexicalBlock(scope: !146, file: !1, line: 89, column: 40)
!155 = !DILocation(line: 90, column: 3, scope: !154)
!156 = !DILocation(line: 91, column: 8, scope: !154)
!157 = !DILocation(line: 91, column: 3, scope: !154)
!158 = !DILocation(line: 92, column: 3, scope: !154)
!159 = !DILocation(line: 94, column: 38, scope: !24)
!160 = !DILocation(line: 94, column: 41, scope: !24)
!161 = !DILocation(line: 94, column: 2, scope: !24)
!162 = !DILocation(line: 95, column: 37, scope: !24)
!163 = !DILocation(line: 95, column: 40, scope: !24)
!164 = !DILocation(line: 95, column: 2, scope: !24)
!165 = !DILocation(line: 96, column: 2, scope: !24)
!166 = !DILocation(line: 97, column: 1, scope: !24)
!167 = !DILocalVariable(name: "private_data", arg: 1, scope: !120, file: !1, line: 100, type: !4)
!168 = !DILocation(line: 100, column: 18, scope: !120)
!169 = !DILocalVariable(name: "gname", arg: 2, scope: !120, file: !1, line: 100, type: !92)
!170 = !DILocation(line: 100, column: 44, scope: !120)
!171 = !DILocalVariable(name: "gid", arg: 3, scope: !120, file: !1, line: 100, type: !64)
!172 = !DILocation(line: 100, column: 59, scope: !120)
!173 = !DILocalVariable(name: "h", scope: !120, file: !1, line: 102, type: !12)
!174 = !DILocation(line: 102, column: 6, scope: !120)
!175 = !DILocalVariable(name: "b", scope: !120, file: !1, line: 103, type: !5)
!176 = !DILocation(line: 103, column: 17, scope: !120)
!177 = !DILocalVariable(name: "gcache", scope: !120, file: !1, line: 104, type: !5)
!178 = !DILocation(line: 104, column: 17, scope: !120)
!179 = !DILocation(line: 104, column: 43, scope: !120)
!180 = !DILocation(line: 104, column: 26, scope: !120)
!181 = !DILocation(line: 107, column: 6, scope: !182)
!182 = distinct !DILexicalBlock(scope: !120, file: !1, line: 107, column: 6)
!183 = !DILocation(line: 107, column: 12, scope: !182)
!184 = !DILocation(line: 107, column: 20, scope: !182)
!185 = !DILocation(line: 107, column: 24, scope: !186)
!186 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 1)
!187 = !DILocation(line: 107, column: 23, scope: !186)
!188 = !DILocation(line: 107, column: 30, scope: !186)
!189 = !DILocation(line: 107, column: 6, scope: !186)
!190 = !DILocation(line: 108, column: 11, scope: !182)
!191 = !DILocation(line: 108, column: 3, scope: !182)
!192 = !DILocation(line: 111, column: 11, scope: !120)
!193 = !DILocation(line: 111, column: 6, scope: !120)
!194 = !DILocation(line: 111, column: 4, scope: !120)
!195 = !DILocation(line: 112, column: 14, scope: !120)
!196 = !DILocation(line: 112, column: 16, scope: !120)
!197 = !DILocation(line: 112, column: 7, scope: !120)
!198 = !DILocation(line: 112, column: 4, scope: !120)
!199 = !DILocation(line: 113, column: 6, scope: !200)
!200 = distinct !DILexicalBlock(scope: !120, file: !1, line: 113, column: 6)
!201 = !DILocation(line: 113, column: 9, scope: !200)
!202 = !DILocation(line: 113, column: 14, scope: !200)
!203 = !DILocation(line: 113, column: 22, scope: !200)
!204 = !DILocation(line: 113, column: 25, scope: !205)
!205 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 1)
!206 = !DILocation(line: 113, column: 28, scope: !205)
!207 = !DILocation(line: 113, column: 36, scope: !205)
!208 = !DILocation(line: 113, column: 33, scope: !205)
!209 = !DILocation(line: 113, column: 38, scope: !205)
!210 = !DILocation(line: 113, column: 48, scope: !211)
!211 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 2)
!212 = !DILocation(line: 113, column: 55, scope: !211)
!213 = !DILocation(line: 113, column: 58, scope: !211)
!214 = !DILocation(line: 113, column: 41, scope: !211)
!215 = !DILocation(line: 113, column: 64, scope: !211)
!216 = !DILocation(line: 113, column: 6, scope: !211)
!217 = !DILocation(line: 114, column: 18, scope: !200)
!218 = !DILocation(line: 114, column: 21, scope: !200)
!219 = !DILocation(line: 114, column: 10, scope: !200)
!220 = !DILocation(line: 114, column: 3, scope: !200)
!221 = !DILocation(line: 117, column: 6, scope: !222)
!222 = distinct !DILexicalBlock(scope: !120, file: !1, line: 117, column: 6)
!223 = !DILocation(line: 117, column: 9, scope: !222)
!224 = !DILocation(line: 117, column: 14, scope: !222)
!225 = !DILocation(line: 117, column: 6, scope: !120)
!226 = !DILocation(line: 118, column: 8, scope: !222)
!227 = !DILocation(line: 118, column: 11, scope: !222)
!228 = !DILocation(line: 118, column: 3, scope: !222)
!229 = !DILocation(line: 119, column: 19, scope: !120)
!230 = !DILocation(line: 119, column: 12, scope: !120)
!231 = !DILocation(line: 119, column: 2, scope: !120)
!232 = !DILocation(line: 119, column: 5, scope: !120)
!233 = !DILocation(line: 119, column: 10, scope: !120)
!234 = !DILocation(line: 121, column: 12, scope: !120)
!235 = !DILocation(line: 121, column: 2, scope: !120)
!236 = !DILocation(line: 121, column: 5, scope: !120)
!237 = !DILocation(line: 121, column: 10, scope: !120)
!238 = !DILocalVariable(name: "_buffer", scope: !239, file: !1, line: 125, type: !240)
!239 = distinct !DILexicalBlock(scope: !120, file: !1, line: 124, column: 2)
!240 = !DICompositeType(tag: DW_TAG_array_type, baseType: !10, size: 1024, align: 8, elements: !241)
!241 = !{!242}
!242 = !DISubrange(count: 128)
!243 = !DILocation(line: 125, column: 8, scope: !239)
!244 = !DILocalVariable(name: "bufsize", scope: !239, file: !1, line: 126, type: !57)
!245 = !DILocation(line: 126, column: 10, scope: !239)
!246 = !DILocalVariable(name: "buffer", scope: !239, file: !1, line: 127, type: !9)
!247 = !DILocation(line: 127, column: 9, scope: !239)
!248 = !DILocation(line: 127, column: 18, scope: !239)
!249 = !DILocalVariable(name: "allocated", scope: !239, file: !1, line: 128, type: !9)
!250 = !DILocation(line: 128, column: 9, scope: !239)
!251 = !DILocalVariable(name: "grent", scope: !239, file: !1, line: 129, type: !252)
!252 = !DICompositeType(tag: DW_TAG_structure_type, name: "group", file: !253, line: 42, size: 256, align: 64, elements: !254)
!253 = !DIFile(filename: "/usr/include/grp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!254 = !{!255, !256, !257, !258}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "gr_name", scope: !252, file: !253, line: 44, baseType: !9, size: 64, align: 64)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "gr_passwd", scope: !252, file: !253, line: 45, baseType: !9, size: 64, align: 64, offset: 64)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "gr_gid", scope: !252, file: !253, line: 46, baseType: !20, size: 32, align: 32, offset: 128)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "gr_mem", scope: !252, file: !253, line: 47, baseType: !259, size: 64, align: 64, offset: 192)
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!260 = !DILocation(line: 129, column: 16, scope: !239)
!261 = !DILocalVariable(name: "result", scope: !239, file: !1, line: 129, type: !262)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !252, size: 64, align: 64)
!263 = !DILocation(line: 129, column: 24, scope: !239)
!264 = !DILocalVariable(name: "r", scope: !239, file: !1, line: 130, type: !12)
!265 = !DILocation(line: 130, column: 7, scope: !239)
!266 = !DILocation(line: 132, column: 3, scope: !239)
!267 = !DILocation(line: 133, column: 11, scope: !268)
!268 = distinct !DILexicalBlock(scope: !269, file: !1, line: 132, column: 12)
!269 = distinct !DILexicalBlock(scope: !270, file: !1, line: 132, column: 3)
!270 = distinct !DILexicalBlock(scope: !239, file: !1, line: 132, column: 3)
!271 = !DILocation(line: 134, column: 19, scope: !268)
!272 = !DILocation(line: 134, column: 34, scope: !268)
!273 = !DILocation(line: 134, column: 42, scope: !268)
!274 = !DILocation(line: 134, column: 8, scope: !268)
!275 = !DILocation(line: 134, column: 6, scope: !268)
!276 = !DILocation(line: 135, column: 8, scope: !277)
!277 = distinct !DILexicalBlock(scope: !268, file: !1, line: 135, column: 8)
!278 = !DILocation(line: 135, column: 10, scope: !277)
!279 = !DILocation(line: 135, column: 8, scope: !268)
!280 = !DILocation(line: 136, column: 5, scope: !277)
!281 = !DILocation(line: 137, column: 8, scope: !282)
!282 = distinct !DILexicalBlock(scope: !268, file: !1, line: 137, column: 8)
!283 = !DILocation(line: 137, column: 10, scope: !282)
!284 = !DILocation(line: 137, column: 8, scope: !268)
!285 = !DILocation(line: 138, column: 5, scope: !282)
!286 = !DILocation(line: 139, column: 12, scope: !268)
!287 = !DILocation(line: 140, column: 9, scope: !268)
!288 = !DILocation(line: 140, column: 4, scope: !268)
!289 = !DILocation(line: 141, column: 23, scope: !268)
!290 = !DILocation(line: 141, column: 16, scope: !268)
!291 = !DILocation(line: 141, column: 14, scope: !268)
!292 = !DILocation(line: 142, column: 8, scope: !293)
!293 = distinct !DILexicalBlock(scope: !268, file: !1, line: 142, column: 8)
!294 = !DILocation(line: 142, column: 18, scope: !293)
!295 = !DILocation(line: 142, column: 8, scope: !268)
!296 = !DILocation(line: 143, column: 5, scope: !293)
!297 = !DILocation(line: 144, column: 13, scope: !268)
!298 = !DILocation(line: 144, column: 11, scope: !268)
!299 = !DILocation(line: 132, column: 3, scope: !300)
!300 = !DILexicalBlockFile(scope: !269, file: !1, discriminator: 1)
!301 = !DILocation(line: 146, column: 7, scope: !302)
!302 = distinct !DILexicalBlock(scope: !239, file: !1, line: 146, column: 7)
!303 = !DILocation(line: 146, column: 14, scope: !302)
!304 = !DILocation(line: 146, column: 7, scope: !239)
!305 = !DILocation(line: 147, column: 10, scope: !302)
!306 = !DILocation(line: 147, column: 18, scope: !302)
!307 = !DILocation(line: 147, column: 8, scope: !302)
!308 = !DILocation(line: 147, column: 4, scope: !302)
!309 = !DILocation(line: 148, column: 8, scope: !239)
!310 = !DILocation(line: 148, column: 3, scope: !239)
!311 = !DILocation(line: 164, column: 17, scope: !120)
!312 = !DILocation(line: 164, column: 10, scope: !120)
!313 = !DILocation(line: 164, column: 2, scope: !120)
!314 = !DILocation(line: 164, column: 5, scope: !120)
!315 = !DILocation(line: 164, column: 8, scope: !120)
!316 = !DILocation(line: 166, column: 10, scope: !120)
!317 = !DILocation(line: 166, column: 2, scope: !120)
!318 = !DILocation(line: 167, column: 1, scope: !120)
!319 = !DILocalVariable(name: "private", arg: 1, scope: !127, file: !1, line: 240, type: !4)
!320 = !DILocation(line: 240, column: 15, scope: !127)
!321 = !DILocalVariable(name: "i", scope: !127, file: !1, line: 242, type: !57)
!322 = !DILocation(line: 242, column: 9, scope: !127)
!323 = !DILocalVariable(name: "cache", scope: !127, file: !1, line: 243, type: !5)
!324 = !DILocation(line: 243, column: 17, scope: !127)
!325 = !DILocation(line: 243, column: 42, scope: !127)
!326 = !DILocation(line: 243, column: 25, scope: !127)
!327 = !DILocation(line: 245, column: 9, scope: !328)
!328 = distinct !DILexicalBlock(scope: !127, file: !1, line: 245, column: 2)
!329 = !DILocation(line: 245, column: 7, scope: !328)
!330 = !DILocation(line: 245, column: 14, scope: !331)
!331 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 1)
!332 = distinct !DILexicalBlock(scope: !328, file: !1, line: 245, column: 2)
!333 = !DILocation(line: 245, column: 16, scope: !331)
!334 = !DILocation(line: 245, column: 2, scope: !331)
!335 = !DILocation(line: 246, column: 14, scope: !332)
!336 = !DILocation(line: 246, column: 8, scope: !332)
!337 = !DILocation(line: 246, column: 17, scope: !332)
!338 = !DILocation(line: 246, column: 3, scope: !332)
!339 = !DILocation(line: 245, column: 31, scope: !340)
!340 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 2)
!341 = !DILocation(line: 245, column: 2, scope: !340)
!342 = !DILocation(line: 247, column: 7, scope: !127)
!343 = !DILocation(line: 247, column: 2, scope: !127)
!344 = !DILocation(line: 248, column: 1, scope: !127)
!345 = !DILocalVariable(name: "private_data", arg: 1, scope: !126, file: !1, line: 170, type: !4)
!346 = !DILocation(line: 170, column: 18, scope: !126)
!347 = !DILocalVariable(name: "uname", arg: 2, scope: !126, file: !1, line: 170, type: !92)
!348 = !DILocation(line: 170, column: 44, scope: !126)
!349 = !DILocalVariable(name: "uid", arg: 3, scope: !126, file: !1, line: 170, type: !64)
!350 = !DILocation(line: 170, column: 59, scope: !126)
!351 = !DILocalVariable(name: "h", scope: !126, file: !1, line: 172, type: !12)
!352 = !DILocation(line: 172, column: 6, scope: !126)
!353 = !DILocalVariable(name: "b", scope: !126, file: !1, line: 173, type: !5)
!354 = !DILocation(line: 173, column: 17, scope: !126)
!355 = !DILocalVariable(name: "ucache", scope: !126, file: !1, line: 174, type: !5)
!356 = !DILocation(line: 174, column: 17, scope: !126)
!357 = !DILocation(line: 174, column: 43, scope: !126)
!358 = !DILocation(line: 174, column: 26, scope: !126)
!359 = !DILocation(line: 177, column: 6, scope: !360)
!360 = distinct !DILexicalBlock(scope: !126, file: !1, line: 177, column: 6)
!361 = !DILocation(line: 177, column: 12, scope: !360)
!362 = !DILocation(line: 177, column: 20, scope: !360)
!363 = !DILocation(line: 177, column: 24, scope: !364)
!364 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 1)
!365 = !DILocation(line: 177, column: 23, scope: !364)
!366 = !DILocation(line: 177, column: 30, scope: !364)
!367 = !DILocation(line: 177, column: 6, scope: !364)
!368 = !DILocation(line: 178, column: 11, scope: !360)
!369 = !DILocation(line: 178, column: 3, scope: !360)
!370 = !DILocation(line: 181, column: 11, scope: !126)
!371 = !DILocation(line: 181, column: 6, scope: !126)
!372 = !DILocation(line: 181, column: 4, scope: !126)
!373 = !DILocation(line: 182, column: 14, scope: !126)
!374 = !DILocation(line: 182, column: 16, scope: !126)
!375 = !DILocation(line: 182, column: 7, scope: !126)
!376 = !DILocation(line: 182, column: 4, scope: !126)
!377 = !DILocation(line: 183, column: 6, scope: !378)
!378 = distinct !DILexicalBlock(scope: !126, file: !1, line: 183, column: 6)
!379 = !DILocation(line: 183, column: 9, scope: !378)
!380 = !DILocation(line: 183, column: 14, scope: !378)
!381 = !DILocation(line: 183, column: 22, scope: !378)
!382 = !DILocation(line: 183, column: 25, scope: !383)
!383 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 1)
!384 = !DILocation(line: 183, column: 28, scope: !383)
!385 = !DILocation(line: 183, column: 36, scope: !383)
!386 = !DILocation(line: 183, column: 33, scope: !383)
!387 = !DILocation(line: 183, column: 38, scope: !383)
!388 = !DILocation(line: 183, column: 48, scope: !389)
!389 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 2)
!390 = !DILocation(line: 183, column: 55, scope: !389)
!391 = !DILocation(line: 183, column: 58, scope: !389)
!392 = !DILocation(line: 183, column: 41, scope: !389)
!393 = !DILocation(line: 183, column: 64, scope: !389)
!394 = !DILocation(line: 183, column: 6, scope: !389)
!395 = !DILocation(line: 184, column: 18, scope: !378)
!396 = !DILocation(line: 184, column: 21, scope: !378)
!397 = !DILocation(line: 184, column: 10, scope: !378)
!398 = !DILocation(line: 184, column: 3, scope: !378)
!399 = !DILocation(line: 187, column: 6, scope: !400)
!400 = distinct !DILexicalBlock(scope: !126, file: !1, line: 187, column: 6)
!401 = !DILocation(line: 187, column: 9, scope: !400)
!402 = !DILocation(line: 187, column: 14, scope: !400)
!403 = !DILocation(line: 187, column: 6, scope: !126)
!404 = !DILocation(line: 188, column: 8, scope: !400)
!405 = !DILocation(line: 188, column: 11, scope: !400)
!406 = !DILocation(line: 188, column: 3, scope: !400)
!407 = !DILocation(line: 189, column: 19, scope: !126)
!408 = !DILocation(line: 189, column: 12, scope: !126)
!409 = !DILocation(line: 189, column: 2, scope: !126)
!410 = !DILocation(line: 189, column: 5, scope: !126)
!411 = !DILocation(line: 189, column: 10, scope: !126)
!412 = !DILocation(line: 191, column: 12, scope: !126)
!413 = !DILocation(line: 191, column: 2, scope: !126)
!414 = !DILocation(line: 191, column: 5, scope: !126)
!415 = !DILocation(line: 191, column: 10, scope: !126)
!416 = !DILocalVariable(name: "_buffer", scope: !417, file: !1, line: 195, type: !240)
!417 = distinct !DILexicalBlock(scope: !126, file: !1, line: 194, column: 2)
!418 = !DILocation(line: 195, column: 8, scope: !417)
!419 = !DILocalVariable(name: "bufsize", scope: !417, file: !1, line: 196, type: !57)
!420 = !DILocation(line: 196, column: 10, scope: !417)
!421 = !DILocalVariable(name: "buffer", scope: !417, file: !1, line: 197, type: !9)
!422 = !DILocation(line: 197, column: 9, scope: !417)
!423 = !DILocation(line: 197, column: 18, scope: !417)
!424 = !DILocalVariable(name: "allocated", scope: !417, file: !1, line: 198, type: !9)
!425 = !DILocation(line: 198, column: 9, scope: !417)
!426 = !DILocalVariable(name: "pwent", scope: !417, file: !1, line: 199, type: !427)
!427 = !DICompositeType(tag: DW_TAG_structure_type, name: "passwd", file: !428, line: 49, size: 384, align: 64, elements: !429)
!428 = !DIFile(filename: "/usr/include/pwd.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!429 = !{!430, !431, !432, !433, !434, !435, !436}
!430 = !DIDerivedType(tag: DW_TAG_member, name: "pw_name", scope: !427, file: !428, line: 51, baseType: !9, size: 64, align: 64)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "pw_passwd", scope: !427, file: !428, line: 52, baseType: !9, size: 64, align: 64, offset: 64)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "pw_uid", scope: !427, file: !428, line: 53, baseType: !22, size: 32, align: 32, offset: 128)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gid", scope: !427, file: !428, line: 54, baseType: !20, size: 32, align: 32, offset: 160)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "pw_gecos", scope: !427, file: !428, line: 55, baseType: !9, size: 64, align: 64, offset: 192)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "pw_dir", scope: !427, file: !428, line: 56, baseType: !9, size: 64, align: 64, offset: 256)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "pw_shell", scope: !427, file: !428, line: 57, baseType: !9, size: 64, align: 64, offset: 320)
!437 = !DILocation(line: 199, column: 17, scope: !417)
!438 = !DILocalVariable(name: "result", scope: !417, file: !1, line: 199, type: !439)
!439 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !427, size: 64, align: 64)
!440 = !DILocation(line: 199, column: 25, scope: !417)
!441 = !DILocalVariable(name: "r", scope: !417, file: !1, line: 200, type: !12)
!442 = !DILocation(line: 200, column: 7, scope: !417)
!443 = !DILocation(line: 202, column: 3, scope: !417)
!444 = !DILocation(line: 203, column: 11, scope: !445)
!445 = distinct !DILexicalBlock(scope: !446, file: !1, line: 202, column: 12)
!446 = distinct !DILexicalBlock(scope: !447, file: !1, line: 202, column: 3)
!447 = distinct !DILexicalBlock(scope: !417, file: !1, line: 202, column: 3)
!448 = !DILocation(line: 204, column: 19, scope: !445)
!449 = !DILocation(line: 204, column: 34, scope: !445)
!450 = !DILocation(line: 204, column: 42, scope: !445)
!451 = !DILocation(line: 204, column: 8, scope: !445)
!452 = !DILocation(line: 204, column: 6, scope: !445)
!453 = !DILocation(line: 205, column: 8, scope: !454)
!454 = distinct !DILexicalBlock(scope: !445, file: !1, line: 205, column: 8)
!455 = !DILocation(line: 205, column: 10, scope: !454)
!456 = !DILocation(line: 205, column: 8, scope: !445)
!457 = !DILocation(line: 206, column: 5, scope: !454)
!458 = !DILocation(line: 207, column: 8, scope: !459)
!459 = distinct !DILexicalBlock(scope: !445, file: !1, line: 207, column: 8)
!460 = !DILocation(line: 207, column: 10, scope: !459)
!461 = !DILocation(line: 207, column: 8, scope: !445)
!462 = !DILocation(line: 208, column: 5, scope: !459)
!463 = !DILocation(line: 209, column: 12, scope: !445)
!464 = !DILocation(line: 210, column: 9, scope: !445)
!465 = !DILocation(line: 210, column: 4, scope: !445)
!466 = !DILocation(line: 211, column: 23, scope: !445)
!467 = !DILocation(line: 211, column: 16, scope: !445)
!468 = !DILocation(line: 211, column: 14, scope: !445)
!469 = !DILocation(line: 212, column: 8, scope: !470)
!470 = distinct !DILexicalBlock(scope: !445, file: !1, line: 212, column: 8)
!471 = !DILocation(line: 212, column: 18, scope: !470)
!472 = !DILocation(line: 212, column: 8, scope: !445)
!473 = !DILocation(line: 213, column: 5, scope: !470)
!474 = !DILocation(line: 214, column: 13, scope: !445)
!475 = !DILocation(line: 214, column: 11, scope: !445)
!476 = !DILocation(line: 202, column: 3, scope: !477)
!477 = !DILexicalBlockFile(scope: !446, file: !1, discriminator: 1)
!478 = !DILocation(line: 216, column: 7, scope: !479)
!479 = distinct !DILexicalBlock(scope: !417, file: !1, line: 216, column: 7)
!480 = !DILocation(line: 216, column: 14, scope: !479)
!481 = !DILocation(line: 216, column: 7, scope: !417)
!482 = !DILocation(line: 217, column: 10, scope: !479)
!483 = !DILocation(line: 217, column: 18, scope: !479)
!484 = !DILocation(line: 217, column: 8, scope: !479)
!485 = !DILocation(line: 217, column: 4, scope: !479)
!486 = !DILocation(line: 218, column: 8, scope: !417)
!487 = !DILocation(line: 218, column: 3, scope: !417)
!488 = !DILocation(line: 234, column: 17, scope: !126)
!489 = !DILocation(line: 234, column: 10, scope: !126)
!490 = !DILocation(line: 234, column: 2, scope: !126)
!491 = !DILocation(line: 234, column: 5, scope: !126)
!492 = !DILocation(line: 234, column: 8, scope: !126)
!493 = !DILocation(line: 236, column: 10, scope: !126)
!494 = !DILocation(line: 236, column: 2, scope: !126)
!495 = !DILocation(line: 237, column: 1, scope: !126)
!496 = !DILocalVariable(name: "p", arg: 1, scope: !123, file: !1, line: 252, type: !92)
!497 = !DILocation(line: 252, column: 18, scope: !123)
!498 = !DILocalVariable(name: "g", scope: !123, file: !1, line: 256, type: !18)
!499 = !DILocation(line: 256, column: 11, scope: !123)
!500 = !DILocalVariable(name: "h", scope: !123, file: !1, line: 256, type: !18)
!501 = !DILocation(line: 256, column: 14, scope: !123)
!502 = !DILocation(line: 257, column: 2, scope: !123)
!503 = !DILocation(line: 257, column: 10, scope: !504)
!504 = !DILexicalBlockFile(scope: !123, file: !1, discriminator: 1)
!505 = !DILocation(line: 257, column: 9, scope: !504)
!506 = !DILocation(line: 257, column: 12, scope: !504)
!507 = !DILocation(line: 257, column: 2, scope: !504)
!508 = !DILocation(line: 258, column: 8, scope: !509)
!509 = distinct !DILexicalBlock(scope: !123, file: !1, line: 257, column: 21)
!510 = !DILocation(line: 258, column: 10, scope: !509)
!511 = !DILocation(line: 258, column: 20, scope: !509)
!512 = !DILocation(line: 258, column: 18, scope: !509)
!513 = !DILocation(line: 258, column: 16, scope: !509)
!514 = !DILocation(line: 258, column: 5, scope: !509)
!515 = !DILocation(line: 259, column: 12, scope: !516)
!516 = distinct !DILexicalBlock(scope: !509, file: !1, line: 259, column: 7)
!517 = !DILocation(line: 259, column: 14, scope: !516)
!518 = !DILocation(line: 259, column: 10, scope: !516)
!519 = !DILocation(line: 259, column: 28, scope: !516)
!520 = !DILocation(line: 259, column: 7, scope: !509)
!521 = !DILocation(line: 260, column: 9, scope: !522)
!522 = distinct !DILexicalBlock(scope: !516, file: !1, line: 259, column: 34)
!523 = !DILocation(line: 260, column: 11, scope: !522)
!524 = !DILocation(line: 260, column: 6, scope: !522)
!525 = !DILocation(line: 261, column: 6, scope: !522)
!526 = !DILocation(line: 262, column: 3, scope: !522)
!527 = !DILocation(line: 257, column: 2, scope: !528)
!528 = !DILexicalBlockFile(scope: !123, file: !1, discriminator: 2)
!529 = !DILocation(line: 264, column: 9, scope: !123)
!530 = !DILocation(line: 264, column: 2, scope: !123)
