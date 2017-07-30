; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_hash = type { %struct.curl_llist*, i64 (i8*, i64, i64)*, i64 (i8*, i64, i8*, i64)*, void (i8*)*, i32, i64 }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%struct.curl_hash_element = type { i8*, i64, [1 x i8] }
%struct.curl_hash_iterator = type { %struct.curl_hash*, i32, %struct.curl_llist_element* }

@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8

; Function Attrs: nounwind uwtable
define i32 @Curl_hash_init(%struct.curl_hash* %h, i32 %slots, i64 (i8*, i64, i64)* %hfunc, i64 (i8*, i64, i8*, i64)* %comparator, void (i8*)* %dtor) #0 !dbg !62 {
entry:
  %retval = alloca i32, align 4
  %h.addr = alloca %struct.curl_hash*, align 8
  %slots.addr = alloca i32, align 4
  %hfunc.addr = alloca i64 (i8*, i64, i64)*, align 8
  %comparator.addr = alloca i64 (i8*, i64, i8*, i64)*, align 8
  %dtor.addr = alloca void (i8*)*, align 8
  %i = alloca i32, align 4
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !107, metadata !108), !dbg !109
  store i32 %slots, i32* %slots.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %slots.addr, metadata !110, metadata !108), !dbg !111
  store i64 (i8*, i64, i64)* %hfunc, i64 (i8*, i64, i64)** %hfunc.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (i8*, i64, i64)** %hfunc.addr, metadata !112, metadata !108), !dbg !113
  store i64 (i8*, i64, i8*, i64)* %comparator, i64 (i8*, i64, i8*, i64)** %comparator.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (i8*, i64, i8*, i64)** %comparator.addr, metadata !114, metadata !108), !dbg !115
  store void (i8*)* %dtor, void (i8*)** %dtor.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %dtor.addr, metadata !116, metadata !108), !dbg !117
  call void @llvm.dbg.declare(metadata i32* %i, metadata !118, metadata !108), !dbg !119
  %0 = load i32, i32* %slots.addr, align 4, !dbg !120
  %tobool = icmp ne i32 %0, 0, !dbg !120
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !122

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64 (i8*, i64, i64)*, i64 (i8*, i64, i64)** %hfunc.addr, align 8, !dbg !123
  %tobool1 = icmp ne i64 (i8*, i64, i64)* %1, null, !dbg !123
  br i1 %tobool1, label %lor.lhs.false2, label %if.then, !dbg !125

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i64 (i8*, i64, i8*, i64)*, i64 (i8*, i64, i8*, i64)** %comparator.addr, align 8, !dbg !126
  %tobool3 = icmp ne i64 (i8*, i64, i8*, i64)* %2, null, !dbg !126
  br i1 %tobool3, label %lor.lhs.false4, label %if.then, !dbg !128

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load void (i8*)*, void (i8*)** %dtor.addr, align 8, !dbg !129
  %tobool5 = icmp ne void (i8*)* %3, null, !dbg !129
  br i1 %tobool5, label %if.end, label %if.then, !dbg !131

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 1, i32* %retval, align 4, !dbg !132
  br label %return, !dbg !132

if.end:                                           ; preds = %lor.lhs.false4
  %4 = load i64 (i8*, i64, i64)*, i64 (i8*, i64, i64)** %hfunc.addr, align 8, !dbg !134
  %5 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !135
  %hash_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %5, i32 0, i32 1, !dbg !136
  store i64 (i8*, i64, i64)* %4, i64 (i8*, i64, i64)** %hash_func, align 8, !dbg !137
  %6 = load i64 (i8*, i64, i8*, i64)*, i64 (i8*, i64, i8*, i64)** %comparator.addr, align 8, !dbg !138
  %7 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !139
  %comp_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %7, i32 0, i32 2, !dbg !140
  store i64 (i8*, i64, i8*, i64)* %6, i64 (i8*, i64, i8*, i64)** %comp_func, align 8, !dbg !141
  %8 = load void (i8*)*, void (i8*)** %dtor.addr, align 8, !dbg !142
  %9 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !143
  %dtor6 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %9, i32 0, i32 3, !dbg !144
  store void (i8*)* %8, void (i8*)** %dtor6, align 8, !dbg !145
  %10 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !146
  %size = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %10, i32 0, i32 5, !dbg !147
  store i64 0, i64* %size, align 8, !dbg !148
  %11 = load i32, i32* %slots.addr, align 4, !dbg !149
  %12 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !150
  %slots7 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %12, i32 0, i32 4, !dbg !151
  store i32 %11, i32* %slots7, align 8, !dbg !152
  %13 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !153
  %14 = load i32, i32* %slots.addr, align 4, !dbg !153
  %conv = sext i32 %14 to i64, !dbg !153
  %mul = mul i64 %conv, 32, !dbg !153
  %call = call i8* %13(i64 %mul), !dbg !153
  %15 = bitcast i8* %call to %struct.curl_llist*, !dbg !153
  %16 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !154
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %16, i32 0, i32 0, !dbg !155
  store %struct.curl_llist* %15, %struct.curl_llist** %table, align 8, !dbg !156
  %17 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !157
  %table8 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %17, i32 0, i32 0, !dbg !159
  %18 = load %struct.curl_llist*, %struct.curl_llist** %table8, align 8, !dbg !159
  %tobool9 = icmp ne %struct.curl_llist* %18, null, !dbg !157
  br i1 %tobool9, label %if.then10, label %if.end13, !dbg !160

if.then10:                                        ; preds = %if.end
  store i32 0, i32* %i, align 4, !dbg !161
  br label %for.cond, !dbg !164

for.cond:                                         ; preds = %for.inc, %if.then10
  %19 = load i32, i32* %i, align 4, !dbg !165
  %20 = load i32, i32* %slots.addr, align 4, !dbg !168
  %cmp = icmp slt i32 %19, %20, !dbg !169
  br i1 %cmp, label %for.body, label %for.end, !dbg !170

for.body:                                         ; preds = %for.cond
  %21 = load i32, i32* %i, align 4, !dbg !171
  %idxprom = sext i32 %21 to i64, !dbg !172
  %22 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !172
  %table12 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %22, i32 0, i32 0, !dbg !173
  %23 = load %struct.curl_llist*, %struct.curl_llist** %table12, align 8, !dbg !173
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %23, i64 %idxprom, !dbg !172
  call void @Curl_llist_init(%struct.curl_llist* %arrayidx, void (i8*, i8*)* @hash_element_dtor), !dbg !174
  br label %for.inc, !dbg !174

for.inc:                                          ; preds = %for.body
  %24 = load i32, i32* %i, align 4, !dbg !175
  %inc = add nsw i32 %24, 1, !dbg !175
  store i32 %inc, i32* %i, align 4, !dbg !175
  br label %for.cond, !dbg !177

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !178
  br label %return, !dbg !178

if.end13:                                         ; preds = %if.end
  %25 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !179
  %slots14 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %25, i32 0, i32 4, !dbg !180
  store i32 0, i32* %slots14, align 8, !dbg !181
  store i32 1, i32* %retval, align 4, !dbg !182
  br label %return, !dbg !182

return:                                           ; preds = %if.end13, %for.end, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !183
  ret i32 %26, !dbg !183
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @Curl_llist_init(%struct.curl_llist*, void (i8*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal void @hash_element_dtor(i8* %user, i8* %element) #0 !dbg !98 {
entry:
  %user.addr = alloca i8*, align 8
  %element.addr = alloca i8*, align 8
  %h = alloca %struct.curl_hash*, align 8
  %e = alloca %struct.curl_hash_element*, align 8
  store i8* %user, i8** %user.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user.addr, metadata !184, metadata !108), !dbg !185
  store i8* %element, i8** %element.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %element.addr, metadata !186, metadata !108), !dbg !187
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h, metadata !188, metadata !108), !dbg !189
  %0 = load i8*, i8** %user.addr, align 8, !dbg !190
  %1 = bitcast i8* %0 to %struct.curl_hash*, !dbg !191
  store %struct.curl_hash* %1, %struct.curl_hash** %h, align 8, !dbg !189
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %e, metadata !192, metadata !108), !dbg !193
  %2 = load i8*, i8** %element.addr, align 8, !dbg !194
  %3 = bitcast i8* %2 to %struct.curl_hash_element*, !dbg !195
  store %struct.curl_hash_element* %3, %struct.curl_hash_element** %e, align 8, !dbg !193
  %4 = load %struct.curl_hash_element*, %struct.curl_hash_element** %e, align 8, !dbg !196
  %ptr = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %4, i32 0, i32 0, !dbg !198
  %5 = load i8*, i8** %ptr, align 8, !dbg !198
  %tobool = icmp ne i8* %5, null, !dbg !196
  br i1 %tobool, label %if.then, label %if.end, !dbg !199

if.then:                                          ; preds = %entry
  %6 = load %struct.curl_hash*, %struct.curl_hash** %h, align 8, !dbg !200
  %dtor = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %6, i32 0, i32 3, !dbg !202
  %7 = load void (i8*)*, void (i8*)** %dtor, align 8, !dbg !202
  %8 = load %struct.curl_hash_element*, %struct.curl_hash_element** %e, align 8, !dbg !203
  %ptr1 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %8, i32 0, i32 0, !dbg !204
  %9 = load i8*, i8** %ptr1, align 8, !dbg !204
  call void %7(i8* %9), !dbg !200
  %10 = load %struct.curl_hash_element*, %struct.curl_hash_element** %e, align 8, !dbg !205
  %ptr2 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %10, i32 0, i32 0, !dbg !206
  store i8* null, i8** %ptr2, align 8, !dbg !207
  br label %if.end, !dbg !208

if.end:                                           ; preds = %if.then, %entry
  %11 = load %struct.curl_hash_element*, %struct.curl_hash_element** %e, align 8, !dbg !209
  %key_len = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %11, i32 0, i32 1, !dbg !210
  store i64 0, i64* %key_len, align 8, !dbg !211
  %12 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !212
  %13 = load %struct.curl_hash_element*, %struct.curl_hash_element** %e, align 8, !dbg !212
  %14 = bitcast %struct.curl_hash_element* %13 to i8*, !dbg !212
  call void %12(i8* %14), !dbg !212
  ret void, !dbg !213
}

; Function Attrs: nounwind uwtable
define i8* @Curl_hash_add(%struct.curl_hash* %h, i8* %key, i64 %key_len, i8* %p) #0 !dbg !65 {
entry:
  %retval = alloca i8*, align 8
  %h.addr = alloca %struct.curl_hash*, align 8
  %key.addr = alloca i8*, align 8
  %key_len.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %he = alloca %struct.curl_hash_element*, align 8
  %le = alloca %struct.curl_llist_element*, align 8
  %l = alloca %struct.curl_llist*, align 8
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !214, metadata !108), !dbg !215
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !216, metadata !108), !dbg !217
  store i64 %key_len, i64* %key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_len.addr, metadata !218, metadata !108), !dbg !219
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !220, metadata !108), !dbg !221
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %he, metadata !222, metadata !108), !dbg !223
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %le, metadata !224, metadata !108), !dbg !225
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %l, metadata !226, metadata !108), !dbg !227
  %0 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !228
  %hash_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %0, i32 0, i32 1, !dbg !228
  %1 = load i64 (i8*, i64, i64)*, i64 (i8*, i64, i64)** %hash_func, align 8, !dbg !228
  %2 = load i8*, i8** %key.addr, align 8, !dbg !228
  %3 = load i64, i64* %key_len.addr, align 8, !dbg !228
  %4 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !228
  %slots = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %4, i32 0, i32 4, !dbg !228
  %5 = load i32, i32* %slots, align 8, !dbg !228
  %conv = sext i32 %5 to i64, !dbg !228
  %call = call i64 %1(i8* %2, i64 %3, i64 %conv), !dbg !228
  %6 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !228
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %6, i32 0, i32 0, !dbg !228
  %7 = load %struct.curl_llist*, %struct.curl_llist** %table, align 8, !dbg !228
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %7, i64 %call, !dbg !228
  store %struct.curl_llist* %arrayidx, %struct.curl_llist** %l, align 8, !dbg !227
  %8 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !229
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %8, i32 0, i32 0, !dbg !231
  %9 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !231
  store %struct.curl_llist_element* %9, %struct.curl_llist_element** %le, align 8, !dbg !232
  br label %for.cond, !dbg !233

for.cond:                                         ; preds = %for.inc, %entry
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !234
  %tobool = icmp ne %struct.curl_llist_element* %10, null, !dbg !237
  br i1 %tobool, label %for.body, label %for.end, !dbg !237

for.body:                                         ; preds = %for.cond
  %11 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !238
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %11, i32 0, i32 0, !dbg !240
  %12 = load i8*, i8** %ptr, align 8, !dbg !240
  %13 = bitcast i8* %12 to %struct.curl_hash_element*, !dbg !241
  store %struct.curl_hash_element* %13, %struct.curl_hash_element** %he, align 8, !dbg !242
  %14 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !243
  %comp_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %14, i32 0, i32 2, !dbg !245
  %15 = load i64 (i8*, i64, i8*, i64)*, i64 (i8*, i64, i8*, i64)** %comp_func, align 8, !dbg !245
  %16 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !246
  %key1 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %16, i32 0, i32 2, !dbg !247
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %key1, i32 0, i32 0, !dbg !246
  %17 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !248
  %key_len2 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %17, i32 0, i32 1, !dbg !249
  %18 = load i64, i64* %key_len2, align 8, !dbg !249
  %19 = load i8*, i8** %key.addr, align 8, !dbg !250
  %20 = load i64, i64* %key_len.addr, align 8, !dbg !251
  %call3 = call i64 %15(i8* %arraydecay, i64 %18, i8* %19, i64 %20), !dbg !243
  %tobool4 = icmp ne i64 %call3, 0, !dbg !243
  br i1 %tobool4, label %if.then, label %if.end, !dbg !252

if.then:                                          ; preds = %for.body
  %21 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !253
  %22 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !255
  %23 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !256
  %24 = bitcast %struct.curl_hash* %23 to i8*, !dbg !257
  %call5 = call i32 @Curl_llist_remove(%struct.curl_llist* %21, %struct.curl_llist_element* %22, i8* %24), !dbg !258
  %25 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !259
  %size = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %25, i32 0, i32 5, !dbg !260
  %26 = load i64, i64* %size, align 8, !dbg !261
  %dec = add i64 %26, -1, !dbg !261
  store i64 %dec, i64* %size, align 8, !dbg !261
  br label %for.end, !dbg !262

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !263

for.inc:                                          ; preds = %if.end
  %27 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !264
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %27, i32 0, i32 2, !dbg !266
  %28 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !266
  store %struct.curl_llist_element* %28, %struct.curl_llist_element** %le, align 8, !dbg !267
  br label %for.cond, !dbg !268

for.end:                                          ; preds = %if.then, %for.cond
  %29 = load i8*, i8** %key.addr, align 8, !dbg !269
  %30 = load i64, i64* %key_len.addr, align 8, !dbg !270
  %31 = load i8*, i8** %p.addr, align 8, !dbg !271
  %call6 = call %struct.curl_hash_element* @mk_hash_element(i8* %29, i64 %30, i8* %31), !dbg !272
  store %struct.curl_hash_element* %call6, %struct.curl_hash_element** %he, align 8, !dbg !273
  %32 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !274
  %tobool7 = icmp ne %struct.curl_hash_element* %32, null, !dbg !274
  br i1 %tobool7, label %if.then8, label %if.end14, !dbg !276

if.then8:                                         ; preds = %for.end
  %33 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !277
  %34 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !280
  %tail = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %34, i32 0, i32 1, !dbg !281
  %35 = load %struct.curl_llist_element*, %struct.curl_llist_element** %tail, align 8, !dbg !281
  %36 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !282
  %37 = bitcast %struct.curl_hash_element* %36 to i8*, !dbg !282
  %call9 = call i32 @Curl_llist_insert_next(%struct.curl_llist* %33, %struct.curl_llist_element* %35, i8* %37), !dbg !283
  %tobool10 = icmp ne i32 %call9, 0, !dbg !283
  br i1 %tobool10, label %if.then11, label %if.end13, !dbg !284

if.then11:                                        ; preds = %if.then8
  %38 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !285
  %size12 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %38, i32 0, i32 5, !dbg !287
  %39 = load i64, i64* %size12, align 8, !dbg !288
  %inc = add i64 %39, 1, !dbg !288
  store i64 %inc, i64* %size12, align 8, !dbg !288
  %40 = load i8*, i8** %p.addr, align 8, !dbg !289
  store i8* %40, i8** %retval, align 8, !dbg !290
  br label %return, !dbg !290

if.end13:                                         ; preds = %if.then8
  %41 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !291
  %42 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !291
  %43 = bitcast %struct.curl_hash_element* %42 to i8*, !dbg !291
  call void %41(i8* %43), !dbg !291
  br label %if.end14, !dbg !292

if.end14:                                         ; preds = %if.end13, %for.end
  store i8* null, i8** %retval, align 8, !dbg !293
  br label %return, !dbg !293

return:                                           ; preds = %if.end14, %if.then11
  %44 = load i8*, i8** %retval, align 8, !dbg !294
  ret i8* %44, !dbg !294
}

declare i32 @Curl_llist_remove(%struct.curl_llist*, %struct.curl_llist_element*, i8*) #2

; Function Attrs: nounwind uwtable
define internal %struct.curl_hash_element* @mk_hash_element(i8* %key, i64 %key_len, i8* %p) #0 !dbg !99 {
entry:
  %key.addr = alloca i8*, align 8
  %key_len.addr = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %he = alloca %struct.curl_hash_element*, align 8
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !295, metadata !108), !dbg !296
  store i64 %key_len, i64* %key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_len.addr, metadata !297, metadata !108), !dbg !298
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !299, metadata !108), !dbg !300
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %he, metadata !301, metadata !108), !dbg !302
  %0 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !303
  %1 = load i64, i64* %key_len.addr, align 8, !dbg !303
  %add = add i64 24, %1, !dbg !303
  %call = call i8* %0(i64 %add), !dbg !303
  %2 = bitcast i8* %call to %struct.curl_hash_element*, !dbg !303
  store %struct.curl_hash_element* %2, %struct.curl_hash_element** %he, align 8, !dbg !302
  %3 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !304
  %tobool = icmp ne %struct.curl_hash_element* %3, null, !dbg !304
  br i1 %tobool, label %if.then, label %if.end, !dbg !306

if.then:                                          ; preds = %entry
  %4 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !307
  %key1 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %4, i32 0, i32 2, !dbg !309
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %key1, i32 0, i32 0, !dbg !310
  %5 = load i8*, i8** %key.addr, align 8, !dbg !311
  %6 = load i64, i64* %key_len.addr, align 8, !dbg !312
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %5, i64 %6, i32 1, i1 false), !dbg !310
  %7 = load i64, i64* %key_len.addr, align 8, !dbg !313
  %8 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !314
  %key_len2 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %8, i32 0, i32 1, !dbg !315
  store i64 %7, i64* %key_len2, align 8, !dbg !316
  %9 = load i8*, i8** %p.addr, align 8, !dbg !317
  %10 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !318
  %ptr = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %10, i32 0, i32 0, !dbg !319
  store i8* %9, i8** %ptr, align 8, !dbg !320
  br label %if.end, !dbg !321

if.end:                                           ; preds = %if.then, %entry
  %11 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !322
  ret %struct.curl_hash_element* %11, !dbg !323
}

declare i32 @Curl_llist_insert_next(%struct.curl_llist*, %struct.curl_llist_element*, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_hash_delete(%struct.curl_hash* %h, i8* %key, i64 %key_len) #0 !dbg !68 {
entry:
  %retval = alloca i32, align 4
  %h.addr = alloca %struct.curl_hash*, align 8
  %key.addr = alloca i8*, align 8
  %key_len.addr = alloca i64, align 8
  %le = alloca %struct.curl_llist_element*, align 8
  %he = alloca %struct.curl_hash_element*, align 8
  %l = alloca %struct.curl_llist*, align 8
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !324, metadata !108), !dbg !325
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !326, metadata !108), !dbg !327
  store i64 %key_len, i64* %key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_len.addr, metadata !328, metadata !108), !dbg !329
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %le, metadata !330, metadata !108), !dbg !331
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %he, metadata !332, metadata !108), !dbg !333
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %l, metadata !334, metadata !108), !dbg !335
  %0 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !336
  %hash_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %0, i32 0, i32 1, !dbg !336
  %1 = load i64 (i8*, i64, i64)*, i64 (i8*, i64, i64)** %hash_func, align 8, !dbg !336
  %2 = load i8*, i8** %key.addr, align 8, !dbg !336
  %3 = load i64, i64* %key_len.addr, align 8, !dbg !336
  %4 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !336
  %slots = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %4, i32 0, i32 4, !dbg !336
  %5 = load i32, i32* %slots, align 8, !dbg !336
  %conv = sext i32 %5 to i64, !dbg !336
  %call = call i64 %1(i8* %2, i64 %3, i64 %conv), !dbg !336
  %6 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !336
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %6, i32 0, i32 0, !dbg !336
  %7 = load %struct.curl_llist*, %struct.curl_llist** %table, align 8, !dbg !336
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %7, i64 %call, !dbg !336
  store %struct.curl_llist* %arrayidx, %struct.curl_llist** %l, align 8, !dbg !335
  %8 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !337
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %8, i32 0, i32 0, !dbg !339
  %9 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !339
  store %struct.curl_llist_element* %9, %struct.curl_llist_element** %le, align 8, !dbg !340
  br label %for.cond, !dbg !341

for.cond:                                         ; preds = %for.inc, %entry
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !342
  %tobool = icmp ne %struct.curl_llist_element* %10, null, !dbg !345
  br i1 %tobool, label %for.body, label %for.end, !dbg !345

for.body:                                         ; preds = %for.cond
  %11 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !346
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %11, i32 0, i32 0, !dbg !348
  %12 = load i8*, i8** %ptr, align 8, !dbg !348
  %13 = bitcast i8* %12 to %struct.curl_hash_element*, !dbg !346
  store %struct.curl_hash_element* %13, %struct.curl_hash_element** %he, align 8, !dbg !349
  %14 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !350
  %comp_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %14, i32 0, i32 2, !dbg !352
  %15 = load i64 (i8*, i64, i8*, i64)*, i64 (i8*, i64, i8*, i64)** %comp_func, align 8, !dbg !352
  %16 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !353
  %key1 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %16, i32 0, i32 2, !dbg !354
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %key1, i32 0, i32 0, !dbg !353
  %17 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !355
  %key_len2 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %17, i32 0, i32 1, !dbg !356
  %18 = load i64, i64* %key_len2, align 8, !dbg !356
  %19 = load i8*, i8** %key.addr, align 8, !dbg !357
  %20 = load i64, i64* %key_len.addr, align 8, !dbg !358
  %call3 = call i64 %15(i8* %arraydecay, i64 %18, i8* %19, i64 %20), !dbg !350
  %tobool4 = icmp ne i64 %call3, 0, !dbg !350
  br i1 %tobool4, label %if.then, label %if.end, !dbg !359

if.then:                                          ; preds = %for.body
  %21 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !360
  %22 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !362
  %23 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !363
  %24 = bitcast %struct.curl_hash* %23 to i8*, !dbg !364
  %call5 = call i32 @Curl_llist_remove(%struct.curl_llist* %21, %struct.curl_llist_element* %22, i8* %24), !dbg !365
  %25 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !366
  %size = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %25, i32 0, i32 5, !dbg !367
  %26 = load i64, i64* %size, align 8, !dbg !368
  %dec = add i64 %26, -1, !dbg !368
  store i64 %dec, i64* %size, align 8, !dbg !368
  store i32 0, i32* %retval, align 4, !dbg !369
  br label %return, !dbg !369

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !370

for.inc:                                          ; preds = %if.end
  %27 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !371
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %27, i32 0, i32 2, !dbg !373
  %28 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !373
  store %struct.curl_llist_element* %28, %struct.curl_llist_element** %le, align 8, !dbg !374
  br label %for.cond, !dbg !375

for.end:                                          ; preds = %for.cond
  store i32 1, i32* %retval, align 4, !dbg !376
  br label %return, !dbg !376

return:                                           ; preds = %for.end, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !377
  ret i32 %29, !dbg !377
}

; Function Attrs: nounwind uwtable
define i8* @Curl_hash_pick(%struct.curl_hash* %h, i8* %key, i64 %key_len) #0 !dbg !71 {
entry:
  %retval = alloca i8*, align 8
  %h.addr = alloca %struct.curl_hash*, align 8
  %key.addr = alloca i8*, align 8
  %key_len.addr = alloca i64, align 8
  %le = alloca %struct.curl_llist_element*, align 8
  %he = alloca %struct.curl_hash_element*, align 8
  %l = alloca %struct.curl_llist*, align 8
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !378, metadata !108), !dbg !379
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !380, metadata !108), !dbg !381
  store i64 %key_len, i64* %key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_len.addr, metadata !382, metadata !108), !dbg !383
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %le, metadata !384, metadata !108), !dbg !385
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %he, metadata !386, metadata !108), !dbg !387
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %l, metadata !388, metadata !108), !dbg !389
  %0 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !390
  %tobool = icmp ne %struct.curl_hash* %0, null, !dbg !390
  br i1 %tobool, label %if.then, label %if.end8, !dbg !392

if.then:                                          ; preds = %entry
  %1 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !393
  %hash_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %1, i32 0, i32 1, !dbg !393
  %2 = load i64 (i8*, i64, i64)*, i64 (i8*, i64, i64)** %hash_func, align 8, !dbg !393
  %3 = load i8*, i8** %key.addr, align 8, !dbg !393
  %4 = load i64, i64* %key_len.addr, align 8, !dbg !393
  %5 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !393
  %slots = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %5, i32 0, i32 4, !dbg !393
  %6 = load i32, i32* %slots, align 8, !dbg !393
  %conv = sext i32 %6 to i64, !dbg !393
  %call = call i64 %2(i8* %3, i64 %4, i64 %conv), !dbg !393
  %7 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !393
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %7, i32 0, i32 0, !dbg !393
  %8 = load %struct.curl_llist*, %struct.curl_llist** %table, align 8, !dbg !393
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %8, i64 %call, !dbg !393
  store %struct.curl_llist* %arrayidx, %struct.curl_llist** %l, align 8, !dbg !395
  %9 = load %struct.curl_llist*, %struct.curl_llist** %l, align 8, !dbg !396
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %9, i32 0, i32 0, !dbg !398
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !398
  store %struct.curl_llist_element* %10, %struct.curl_llist_element** %le, align 8, !dbg !399
  br label %for.cond, !dbg !400

for.cond:                                         ; preds = %for.inc, %if.then
  %11 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !401
  %tobool1 = icmp ne %struct.curl_llist_element* %11, null, !dbg !404
  br i1 %tobool1, label %for.body, label %for.end, !dbg !404

for.body:                                         ; preds = %for.cond
  %12 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !405
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %12, i32 0, i32 0, !dbg !407
  %13 = load i8*, i8** %ptr, align 8, !dbg !407
  %14 = bitcast i8* %13 to %struct.curl_hash_element*, !dbg !405
  store %struct.curl_hash_element* %14, %struct.curl_hash_element** %he, align 8, !dbg !408
  %15 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !409
  %comp_func = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %15, i32 0, i32 2, !dbg !411
  %16 = load i64 (i8*, i64, i8*, i64)*, i64 (i8*, i64, i8*, i64)** %comp_func, align 8, !dbg !411
  %17 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !412
  %key2 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %17, i32 0, i32 2, !dbg !413
  %arraydecay = getelementptr inbounds [1 x i8], [1 x i8]* %key2, i32 0, i32 0, !dbg !412
  %18 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !414
  %key_len3 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %18, i32 0, i32 1, !dbg !415
  %19 = load i64, i64* %key_len3, align 8, !dbg !415
  %20 = load i8*, i8** %key.addr, align 8, !dbg !416
  %21 = load i64, i64* %key_len.addr, align 8, !dbg !417
  %call4 = call i64 %16(i8* %arraydecay, i64 %19, i8* %20, i64 %21), !dbg !409
  %tobool5 = icmp ne i64 %call4, 0, !dbg !409
  br i1 %tobool5, label %if.then6, label %if.end, !dbg !418

if.then6:                                         ; preds = %for.body
  %22 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !419
  %ptr7 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %22, i32 0, i32 0, !dbg !421
  %23 = load i8*, i8** %ptr7, align 8, !dbg !421
  store i8* %23, i8** %retval, align 8, !dbg !422
  br label %return, !dbg !422

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !423

for.inc:                                          ; preds = %if.end
  %24 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !424
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %24, i32 0, i32 2, !dbg !426
  %25 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !426
  store %struct.curl_llist_element* %25, %struct.curl_llist_element** %le, align 8, !dbg !427
  br label %for.cond, !dbg !428

for.end:                                          ; preds = %for.cond
  br label %if.end8, !dbg !429

if.end8:                                          ; preds = %for.end, %entry
  store i8* null, i8** %retval, align 8, !dbg !430
  br label %return, !dbg !430

return:                                           ; preds = %if.end8, %if.then6
  %26 = load i8*, i8** %retval, align 8, !dbg !431
  ret i8* %26, !dbg !431
}

; Function Attrs: nounwind uwtable
define void @Curl_hash_destroy(%struct.curl_hash* %h) #0 !dbg !74 {
entry:
  %h.addr = alloca %struct.curl_hash*, align 8
  %i = alloca i32, align 4
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !432, metadata !108), !dbg !433
  call void @llvm.dbg.declare(metadata i32* %i, metadata !434, metadata !108), !dbg !435
  store i32 0, i32* %i, align 4, !dbg !436
  br label %for.cond, !dbg !438

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !439
  %1 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !442
  %slots = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %1, i32 0, i32 4, !dbg !443
  %2 = load i32, i32* %slots, align 8, !dbg !443
  %cmp = icmp slt i32 %0, %2, !dbg !444
  br i1 %cmp, label %for.body, label %for.end, !dbg !445

for.body:                                         ; preds = %for.cond
  %3 = load i32, i32* %i, align 4, !dbg !446
  %idxprom = sext i32 %3 to i64, !dbg !448
  %4 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !448
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %4, i32 0, i32 0, !dbg !449
  %5 = load %struct.curl_llist*, %struct.curl_llist** %table, align 8, !dbg !449
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %5, i64 %idxprom, !dbg !448
  %6 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !450
  %7 = bitcast %struct.curl_hash* %6 to i8*, !dbg !451
  call void @Curl_llist_destroy(%struct.curl_llist* %arrayidx, i8* %7), !dbg !452
  br label %for.inc, !dbg !453

for.inc:                                          ; preds = %for.body
  %8 = load i32, i32* %i, align 4, !dbg !454
  %inc = add nsw i32 %8, 1, !dbg !454
  store i32 %inc, i32* %i, align 4, !dbg !454
  br label %for.cond, !dbg !456

for.end:                                          ; preds = %for.cond
  br label %do.body, !dbg !457

do.body:                                          ; preds = %for.end
  %9 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !458
  %10 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !458
  %table1 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %10, i32 0, i32 0, !dbg !458
  %11 = load %struct.curl_llist*, %struct.curl_llist** %table1, align 8, !dbg !458
  %12 = bitcast %struct.curl_llist* %11 to i8*, !dbg !458
  call void %9(i8* %12), !dbg !458
  %13 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !458
  %table2 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %13, i32 0, i32 0, !dbg !458
  store %struct.curl_llist* null, %struct.curl_llist** %table2, align 8, !dbg !458
  br label %do.end, !dbg !458

do.end:                                           ; preds = %do.body
  %14 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !461
  %size = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %14, i32 0, i32 5, !dbg !462
  store i64 0, i64* %size, align 8, !dbg !463
  %15 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !464
  %slots3 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %15, i32 0, i32 4, !dbg !465
  store i32 0, i32* %slots3, align 8, !dbg !466
  ret void, !dbg !467
}

declare void @Curl_llist_destroy(%struct.curl_llist*, i8*) #2

; Function Attrs: nounwind uwtable
define void @Curl_hash_clean(%struct.curl_hash* %h) #0 !dbg !77 {
entry:
  %h.addr = alloca %struct.curl_hash*, align 8
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !468, metadata !108), !dbg !469
  %0 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !470
  call void @Curl_hash_clean_with_criterium(%struct.curl_hash* %0, i8* null, i32 (i8*, i8*)* null), !dbg !471
  ret void, !dbg !472
}

; Function Attrs: nounwind uwtable
define void @Curl_hash_clean_with_criterium(%struct.curl_hash* %h, i8* %user, i32 (i8*, i8*)* %comp) #0 !dbg !78 {
entry:
  %h.addr = alloca %struct.curl_hash*, align 8
  %user.addr = alloca i8*, align 8
  %comp.addr = alloca i32 (i8*, i8*)*, align 8
  %le = alloca %struct.curl_llist_element*, align 8
  %lnext = alloca %struct.curl_llist_element*, align 8
  %list = alloca %struct.curl_llist*, align 8
  %i = alloca i32, align 4
  %he = alloca %struct.curl_hash_element*, align 8
  store %struct.curl_hash* %h, %struct.curl_hash** %h.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h.addr, metadata !473, metadata !108), !dbg !474
  store i8* %user, i8** %user.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user.addr, metadata !475, metadata !108), !dbg !476
  store i32 (i8*, i8*)* %comp, i32 (i8*, i8*)** %comp.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (i8*, i8*)** %comp.addr, metadata !477, metadata !108), !dbg !478
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %le, metadata !479, metadata !108), !dbg !480
  call void @llvm.dbg.declare(metadata %struct.curl_llist_element** %lnext, metadata !481, metadata !108), !dbg !482
  call void @llvm.dbg.declare(metadata %struct.curl_llist** %list, metadata !483, metadata !108), !dbg !484
  call void @llvm.dbg.declare(metadata i32* %i, metadata !485, metadata !108), !dbg !486
  %0 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !487
  %tobool = icmp ne %struct.curl_hash* %0, null, !dbg !487
  br i1 %tobool, label %if.end, label %if.then, !dbg !489

if.then:                                          ; preds = %entry
  br label %for.end, !dbg !490

if.end:                                           ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !491
  br label %for.cond, !dbg !493

for.cond:                                         ; preds = %for.inc, %if.end
  %1 = load i32, i32* %i, align 4, !dbg !494
  %2 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !497
  %slots = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %2, i32 0, i32 4, !dbg !498
  %3 = load i32, i32* %slots, align 8, !dbg !498
  %cmp = icmp slt i32 %1, %3, !dbg !499
  br i1 %cmp, label %for.body, label %for.end, !dbg !500

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !501
  %idxprom = sext i32 %4 to i64, !dbg !503
  %5 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !503
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %5, i32 0, i32 0, !dbg !504
  %6 = load %struct.curl_llist*, %struct.curl_llist** %table, align 8, !dbg !504
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %6, i64 %idxprom, !dbg !503
  store %struct.curl_llist* %arrayidx, %struct.curl_llist** %list, align 8, !dbg !505
  %7 = load %struct.curl_llist*, %struct.curl_llist** %list, align 8, !dbg !506
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %7, i32 0, i32 0, !dbg !507
  %8 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !507
  store %struct.curl_llist_element* %8, %struct.curl_llist_element** %le, align 8, !dbg !508
  br label %while.cond, !dbg !509

while.cond:                                       ; preds = %if.end7, %for.body
  %9 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !510
  %tobool1 = icmp ne %struct.curl_llist_element* %9, null, !dbg !512
  br i1 %tobool1, label %while.body, label %while.end, !dbg !512

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %he, metadata !513, metadata !108), !dbg !515
  %10 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !516
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %10, i32 0, i32 0, !dbg !517
  %11 = load i8*, i8** %ptr, align 8, !dbg !517
  %12 = bitcast i8* %11 to %struct.curl_hash_element*, !dbg !516
  store %struct.curl_hash_element* %12, %struct.curl_hash_element** %he, align 8, !dbg !515
  %13 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !518
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %13, i32 0, i32 2, !dbg !519
  %14 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !519
  store %struct.curl_llist_element* %14, %struct.curl_llist_element** %lnext, align 8, !dbg !520
  %15 = load i32 (i8*, i8*)*, i32 (i8*, i8*)** %comp.addr, align 8, !dbg !521
  %cmp2 = icmp eq i32 (i8*, i8*)* %15, null, !dbg !523
  br i1 %cmp2, label %if.then5, label %lor.lhs.false, !dbg !524

lor.lhs.false:                                    ; preds = %while.body
  %16 = load i32 (i8*, i8*)*, i32 (i8*, i8*)** %comp.addr, align 8, !dbg !525
  %17 = load i8*, i8** %user.addr, align 8, !dbg !527
  %18 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !528
  %ptr3 = getelementptr inbounds %struct.curl_hash_element, %struct.curl_hash_element* %18, i32 0, i32 0, !dbg !529
  %19 = load i8*, i8** %ptr3, align 8, !dbg !529
  %call = call i32 %16(i8* %17, i8* %19), !dbg !525
  %tobool4 = icmp ne i32 %call, 0, !dbg !525
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !530

if.then5:                                         ; preds = %lor.lhs.false, %while.body
  %20 = load %struct.curl_llist*, %struct.curl_llist** %list, align 8, !dbg !531
  %21 = load %struct.curl_llist_element*, %struct.curl_llist_element** %le, align 8, !dbg !533
  %22 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !534
  %23 = bitcast %struct.curl_hash* %22 to i8*, !dbg !535
  %call6 = call i32 @Curl_llist_remove(%struct.curl_llist* %20, %struct.curl_llist_element* %21, i8* %23), !dbg !536
  %24 = load %struct.curl_hash*, %struct.curl_hash** %h.addr, align 8, !dbg !537
  %size = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %24, i32 0, i32 5, !dbg !538
  %25 = load i64, i64* %size, align 8, !dbg !539
  %dec = add i64 %25, -1, !dbg !539
  store i64 %dec, i64* %size, align 8, !dbg !539
  br label %if.end7, !dbg !540

if.end7:                                          ; preds = %if.then5, %lor.lhs.false
  %26 = load %struct.curl_llist_element*, %struct.curl_llist_element** %lnext, align 8, !dbg !541
  store %struct.curl_llist_element* %26, %struct.curl_llist_element** %le, align 8, !dbg !542
  br label %while.cond, !dbg !543

while.end:                                        ; preds = %while.cond
  br label %for.inc, !dbg !545

for.inc:                                          ; preds = %while.end
  %27 = load i32, i32* %i, align 4, !dbg !546
  %inc = add nsw i32 %27, 1, !dbg !546
  store i32 %inc, i32* %i, align 4, !dbg !546
  br label %for.cond, !dbg !548

for.end:                                          ; preds = %if.then, %for.cond
  ret void, !dbg !549
}

; Function Attrs: nounwind uwtable
define i64 @Curl_hash_str(i8* %key, i64 %key_length, i64 %slots_num) #0 !dbg !84 {
entry:
  %key.addr = alloca i8*, align 8
  %key_length.addr = alloca i64, align 8
  %slots_num.addr = alloca i64, align 8
  %key_str = alloca i8*, align 8
  %end = alloca i8*, align 8
  %h = alloca i64, align 8
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !550, metadata !108), !dbg !551
  store i64 %key_length, i64* %key_length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_length.addr, metadata !552, metadata !108), !dbg !553
  store i64 %slots_num, i64* %slots_num.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %slots_num.addr, metadata !554, metadata !108), !dbg !555
  call void @llvm.dbg.declare(metadata i8** %key_str, metadata !556, metadata !108), !dbg !557
  %0 = load i8*, i8** %key.addr, align 8, !dbg !558
  store i8* %0, i8** %key_str, align 8, !dbg !557
  call void @llvm.dbg.declare(metadata i8** %end, metadata !559, metadata !108), !dbg !560
  %1 = load i8*, i8** %key_str, align 8, !dbg !561
  %2 = load i64, i64* %key_length.addr, align 8, !dbg !562
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %2, !dbg !563
  store i8* %add.ptr, i8** %end, align 8, !dbg !560
  call void @llvm.dbg.declare(metadata i64* %h, metadata !564, metadata !108), !dbg !565
  store i64 5381, i64* %h, align 8, !dbg !565
  br label %while.cond, !dbg !566

while.cond:                                       ; preds = %while.body, %entry
  %3 = load i8*, i8** %key_str, align 8, !dbg !567
  %4 = load i8*, i8** %end, align 8, !dbg !569
  %cmp = icmp ult i8* %3, %4, !dbg !570
  br i1 %cmp, label %while.body, label %while.end, !dbg !571

while.body:                                       ; preds = %while.cond
  %5 = load i64, i64* %h, align 8, !dbg !572
  %shl = shl i64 %5, 5, !dbg !574
  %6 = load i64, i64* %h, align 8, !dbg !575
  %add = add i64 %6, %shl, !dbg !575
  store i64 %add, i64* %h, align 8, !dbg !575
  %7 = load i8*, i8** %key_str, align 8, !dbg !576
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !576
  store i8* %incdec.ptr, i8** %key_str, align 8, !dbg !576
  %8 = load i8, i8* %7, align 1, !dbg !577
  %conv = sext i8 %8 to i64, !dbg !578
  %9 = load i64, i64* %h, align 8, !dbg !579
  %xor = xor i64 %9, %conv, !dbg !579
  store i64 %xor, i64* %h, align 8, !dbg !579
  br label %while.cond, !dbg !580

while.end:                                        ; preds = %while.cond
  %10 = load i64, i64* %h, align 8, !dbg !582
  %11 = load i64, i64* %slots_num.addr, align 8, !dbg !583
  %rem = urem i64 %10, %11, !dbg !584
  ret i64 %rem, !dbg !585
}

; Function Attrs: nounwind uwtable
define i64 @Curl_str_key_compare(i8* %k1, i64 %key1_len, i8* %k2, i64 %key2_len) #0 !dbg !85 {
entry:
  %retval = alloca i64, align 8
  %k1.addr = alloca i8*, align 8
  %key1_len.addr = alloca i64, align 8
  %k2.addr = alloca i8*, align 8
  %key2_len.addr = alloca i64, align 8
  store i8* %k1, i8** %k1.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %k1.addr, metadata !586, metadata !108), !dbg !587
  store i64 %key1_len, i64* %key1_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key1_len.addr, metadata !588, metadata !108), !dbg !589
  store i8* %k2, i8** %k2.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %k2.addr, metadata !590, metadata !108), !dbg !591
  store i64 %key2_len, i64* %key2_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key2_len.addr, metadata !592, metadata !108), !dbg !593
  %0 = load i64, i64* %key1_len.addr, align 8, !dbg !594
  %1 = load i64, i64* %key2_len.addr, align 8, !dbg !596
  %cmp = icmp eq i64 %0, %1, !dbg !597
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !598

land.lhs.true:                                    ; preds = %entry
  %2 = load i8*, i8** %k1.addr, align 8, !dbg !599
  %3 = load i8*, i8** %k2.addr, align 8, !dbg !601
  %4 = load i64, i64* %key1_len.addr, align 8, !dbg !602
  %call = call i32 @memcmp(i8* %2, i8* %3, i64 %4) #5, !dbg !603
  %tobool = icmp ne i32 %call, 0, !dbg !603
  br i1 %tobool, label %if.end, label %if.then, !dbg !604

if.then:                                          ; preds = %land.lhs.true
  store i64 1, i64* %retval, align 8, !dbg !605
  br label %return, !dbg !605

if.end:                                           ; preds = %land.lhs.true, %entry
  store i64 0, i64* %retval, align 8, !dbg !606
  br label %return, !dbg !606

return:                                           ; preds = %if.end, %if.then
  %5 = load i64, i64* %retval, align 8, !dbg !607
  ret i64 %5, !dbg !607
}

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

; Function Attrs: nounwind uwtable
define void @Curl_hash_start_iterate(%struct.curl_hash* %hash, %struct.curl_hash_iterator* %iter) #0 !dbg !86 {
entry:
  %hash.addr = alloca %struct.curl_hash*, align 8
  %iter.addr = alloca %struct.curl_hash_iterator*, align 8
  store %struct.curl_hash* %hash, %struct.curl_hash** %hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %hash.addr, metadata !608, metadata !108), !dbg !609
  store %struct.curl_hash_iterator* %iter, %struct.curl_hash_iterator** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash_iterator** %iter.addr, metadata !610, metadata !108), !dbg !611
  %0 = load %struct.curl_hash*, %struct.curl_hash** %hash.addr, align 8, !dbg !612
  %1 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !613
  %hash1 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %1, i32 0, i32 0, !dbg !614
  store %struct.curl_hash* %0, %struct.curl_hash** %hash1, align 8, !dbg !615
  %2 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !616
  %slot_index = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %2, i32 0, i32 1, !dbg !617
  store i32 0, i32* %slot_index, align 8, !dbg !618
  %3 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !619
  %current_element = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %3, i32 0, i32 2, !dbg !620
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %current_element, align 8, !dbg !621
  ret void, !dbg !622
}

; Function Attrs: nounwind uwtable
define %struct.curl_hash_element* @Curl_hash_next_element(%struct.curl_hash_iterator* %iter) #0 !dbg !95 {
entry:
  %retval = alloca %struct.curl_hash_element*, align 8
  %iter.addr = alloca %struct.curl_hash_iterator*, align 8
  %i = alloca i32, align 4
  %h = alloca %struct.curl_hash*, align 8
  %he = alloca %struct.curl_hash_element*, align 8
  store %struct.curl_hash_iterator* %iter, %struct.curl_hash_iterator** %iter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash_iterator** %iter.addr, metadata !623, metadata !108), !dbg !624
  call void @llvm.dbg.declare(metadata i32* %i, metadata !625, metadata !108), !dbg !626
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %h, metadata !627, metadata !108), !dbg !628
  %0 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !629
  %hash = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %0, i32 0, i32 0, !dbg !630
  %1 = load %struct.curl_hash*, %struct.curl_hash** %hash, align 8, !dbg !630
  store %struct.curl_hash* %1, %struct.curl_hash** %h, align 8, !dbg !628
  %2 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !631
  %current_element = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %2, i32 0, i32 2, !dbg !633
  %3 = load %struct.curl_llist_element*, %struct.curl_llist_element** %current_element, align 8, !dbg !633
  %tobool = icmp ne %struct.curl_llist_element* %3, null, !dbg !631
  br i1 %tobool, label %if.then, label %if.end, !dbg !634

if.then:                                          ; preds = %entry
  %4 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !635
  %current_element1 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %4, i32 0, i32 2, !dbg !636
  %5 = load %struct.curl_llist_element*, %struct.curl_llist_element** %current_element1, align 8, !dbg !636
  %next = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %5, i32 0, i32 2, !dbg !637
  %6 = load %struct.curl_llist_element*, %struct.curl_llist_element** %next, align 8, !dbg !637
  %7 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !638
  %current_element2 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %7, i32 0, i32 2, !dbg !639
  store %struct.curl_llist_element* %6, %struct.curl_llist_element** %current_element2, align 8, !dbg !640
  br label %if.end, !dbg !638

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !641
  %current_element3 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %8, i32 0, i32 2, !dbg !643
  %9 = load %struct.curl_llist_element*, %struct.curl_llist_element** %current_element3, align 8, !dbg !643
  %tobool4 = icmp ne %struct.curl_llist_element* %9, null, !dbg !641
  br i1 %tobool4, label %if.end15, label %if.then5, !dbg !644

if.then5:                                         ; preds = %if.end
  %10 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !645
  %slot_index = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %10, i32 0, i32 1, !dbg !648
  %11 = load i32, i32* %slot_index, align 8, !dbg !648
  store i32 %11, i32* %i, align 4, !dbg !649
  br label %for.cond, !dbg !650

for.cond:                                         ; preds = %for.inc, %if.then5
  %12 = load i32, i32* %i, align 4, !dbg !651
  %13 = load %struct.curl_hash*, %struct.curl_hash** %h, align 8, !dbg !654
  %slots = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %13, i32 0, i32 4, !dbg !655
  %14 = load i32, i32* %slots, align 8, !dbg !655
  %cmp = icmp slt i32 %12, %14, !dbg !656
  br i1 %cmp, label %for.body, label %for.end, !dbg !657

for.body:                                         ; preds = %for.cond
  %15 = load i32, i32* %i, align 4, !dbg !658
  %idxprom = sext i32 %15 to i64, !dbg !661
  %16 = load %struct.curl_hash*, %struct.curl_hash** %h, align 8, !dbg !661
  %table = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %16, i32 0, i32 0, !dbg !662
  %17 = load %struct.curl_llist*, %struct.curl_llist** %table, align 8, !dbg !662
  %arrayidx = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %17, i64 %idxprom, !dbg !661
  %head = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %arrayidx, i32 0, i32 0, !dbg !663
  %18 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head, align 8, !dbg !663
  %tobool6 = icmp ne %struct.curl_llist_element* %18, null, !dbg !661
  br i1 %tobool6, label %if.then7, label %if.end14, !dbg !664

if.then7:                                         ; preds = %for.body
  %19 = load i32, i32* %i, align 4, !dbg !665
  %idxprom8 = sext i32 %19 to i64, !dbg !667
  %20 = load %struct.curl_hash*, %struct.curl_hash** %h, align 8, !dbg !667
  %table9 = getelementptr inbounds %struct.curl_hash, %struct.curl_hash* %20, i32 0, i32 0, !dbg !668
  %21 = load %struct.curl_llist*, %struct.curl_llist** %table9, align 8, !dbg !668
  %arrayidx10 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %21, i64 %idxprom8, !dbg !667
  %head11 = getelementptr inbounds %struct.curl_llist, %struct.curl_llist* %arrayidx10, i32 0, i32 0, !dbg !669
  %22 = load %struct.curl_llist_element*, %struct.curl_llist_element** %head11, align 8, !dbg !669
  %23 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !670
  %current_element12 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %23, i32 0, i32 2, !dbg !671
  store %struct.curl_llist_element* %22, %struct.curl_llist_element** %current_element12, align 8, !dbg !672
  %24 = load i32, i32* %i, align 4, !dbg !673
  %add = add nsw i32 %24, 1, !dbg !674
  %25 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !675
  %slot_index13 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %25, i32 0, i32 1, !dbg !676
  store i32 %add, i32* %slot_index13, align 8, !dbg !677
  br label %for.end, !dbg !678

if.end14:                                         ; preds = %for.body
  br label %for.inc, !dbg !679

for.inc:                                          ; preds = %if.end14
  %26 = load i32, i32* %i, align 4, !dbg !680
  %inc = add nsw i32 %26, 1, !dbg !680
  store i32 %inc, i32* %i, align 4, !dbg !680
  br label %for.cond, !dbg !682

for.end:                                          ; preds = %if.then7, %for.cond
  br label %if.end15, !dbg !683

if.end15:                                         ; preds = %for.end, %if.end
  %27 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !684
  %current_element16 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %27, i32 0, i32 2, !dbg !686
  %28 = load %struct.curl_llist_element*, %struct.curl_llist_element** %current_element16, align 8, !dbg !686
  %tobool17 = icmp ne %struct.curl_llist_element* %28, null, !dbg !684
  br i1 %tobool17, label %if.then18, label %if.end20, !dbg !687

if.then18:                                        ; preds = %if.end15
  call void @llvm.dbg.declare(metadata %struct.curl_hash_element** %he, metadata !688, metadata !108), !dbg !690
  %29 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !691
  %current_element19 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %29, i32 0, i32 2, !dbg !692
  %30 = load %struct.curl_llist_element*, %struct.curl_llist_element** %current_element19, align 8, !dbg !692
  %ptr = getelementptr inbounds %struct.curl_llist_element, %struct.curl_llist_element* %30, i32 0, i32 0, !dbg !693
  %31 = load i8*, i8** %ptr, align 8, !dbg !693
  %32 = bitcast i8* %31 to %struct.curl_hash_element*, !dbg !691
  store %struct.curl_hash_element* %32, %struct.curl_hash_element** %he, align 8, !dbg !690
  %33 = load %struct.curl_hash_element*, %struct.curl_hash_element** %he, align 8, !dbg !694
  store %struct.curl_hash_element* %33, %struct.curl_hash_element** %retval, align 8, !dbg !695
  br label %return, !dbg !695

if.end20:                                         ; preds = %if.end15
  %34 = load %struct.curl_hash_iterator*, %struct.curl_hash_iterator** %iter.addr, align 8, !dbg !696
  %current_element21 = getelementptr inbounds %struct.curl_hash_iterator, %struct.curl_hash_iterator* %34, i32 0, i32 2, !dbg !697
  store %struct.curl_llist_element* null, %struct.curl_llist_element** %current_element21, align 8, !dbg !698
  store %struct.curl_hash_element* null, %struct.curl_hash_element** %retval, align 8, !dbg !699
  br label %return, !dbg !699

return:                                           ; preds = %if.end20, %if.then18
  %35 = load %struct.curl_hash_element*, %struct.curl_hash_element** %retval, align 8, !dbg !700
  ret %struct.curl_hash_element* %35, !dbg !700
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!104, !105}
!llvm.ident = !{!106}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !61)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{}
!3 = !{!4, !10, !9, !24, !18, !26}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !5, line: 28, baseType: !6)
!5 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!7 = !DISubroutineType(types: !8)
!8 = !{null, !9, !9}
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash_element", file: !12, line: 59, size: 192, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!13 = !{!14, !15, !19}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !11, file: !12, line: 60, baseType: !9, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "key_len", scope: !11, file: !12, line: 61, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !17, line: 62, baseType: !18)
!17 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!18 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !11, file: !12, line: 62, baseType: !20, size: 8, align: 8, offset: 128)
!20 = !DICompositeType(tag: DW_TAG_array_type, baseType: !21, size: 8, align: 8, elements: !22)
!21 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!22 = !{!23}
!23 = !DISubrange(count: 1)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !21)
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash", file: !12, line: 46, size: 384, align: 64, elements: !28)
!28 = !{!29, !43, !48, !53, !58, !60}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "table", scope: !27, file: !12, line: 47, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !5, line: 37, size: 256, align: 64, elements: !32)
!32 = !{!33, !40, !41, !42}
!33 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !31, file: !5, line: 38, baseType: !34, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !5, line: 30, size: 192, align: 64, elements: !36)
!36 = !{!37, !38, !39}
!37 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !35, file: !5, line: 31, baseType: !9, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !35, file: !5, line: 33, baseType: !34, size: 64, align: 64, offset: 64)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !35, file: !5, line: 34, baseType: !34, size: 64, align: 64, offset: 128)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !31, file: !5, line: 39, baseType: !34, size: 64, align: 64, offset: 64)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !31, file: !5, line: 41, baseType: !4, size: 64, align: 64, offset: 128)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !31, file: !5, line: 43, baseType: !16, size: 64, align: 64, offset: 192)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "hash_func", scope: !27, file: !12, line: 50, baseType: !44, size: 64, align: 64, offset: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "hash_function", file: !12, line: 32, baseType: !45)
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!46 = !DISubroutineType(types: !47)
!47 = !{!16, !9, !16, !16}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "comp_func", scope: !27, file: !12, line: 53, baseType: !49, size: 64, align: 64, offset: 128)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "comp_function", file: !12, line: 39, baseType: !50)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DISubroutineType(types: !52)
!52 = !{!16, !9, !16, !9, !16}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !27, file: !12, line: 54, baseType: !54, size: 64, align: 64, offset: 192)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_hash_dtor", file: !12, line: 44, baseType: !55)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{null, !9}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "slots", scope: !27, file: !12, line: 55, baseType: !59, size: 32, align: 32, offset: 256)
!59 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !27, file: !12, line: 56, baseType: !16, size: 64, align: 64, offset: 320)
!61 = !{!62, !65, !68, !71, !74, !77, !78, !84, !85, !86, !95, !98, !99}
!62 = distinct !DISubprogram(name: "Curl_hash_init", scope: !1, file: !1, line: 57, type: !63, isLocal: false, isDefinition: true, scopeLine: 62, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!63 = !DISubroutineType(types: !64)
!64 = !{!59, !26, !59, !44, !49, !54}
!65 = distinct !DISubprogram(name: "Curl_hash_add", scope: !1, file: !1, line: 110, type: !66, isLocal: false, isDefinition: true, scopeLine: 111, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!66 = !DISubroutineType(types: !67)
!67 = !{!9, !26, !9, !16, !9}
!68 = distinct !DISubprogram(name: "Curl_hash_delete", scope: !1, file: !1, line: 148, type: !69, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!69 = !DISubroutineType(types: !70)
!70 = !{!59, !26, !9, !16}
!71 = distinct !DISubprogram(name: "Curl_hash_pick", scope: !1, file: !1, line: 170, type: !72, isLocal: false, isDefinition: true, scopeLine: 171, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!72 = !DISubroutineType(types: !73)
!73 = !{!9, !26, !9, !16}
!74 = distinct !DISubprogram(name: "Curl_hash_destroy", scope: !1, file: !1, line: 216, type: !75, isLocal: false, isDefinition: true, scopeLine: 217, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!75 = !DISubroutineType(types: !76)
!76 = !{null, !26}
!77 = distinct !DISubprogram(name: "Curl_hash_clean", scope: !1, file: !1, line: 234, type: !75, isLocal: false, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!78 = distinct !DISubprogram(name: "Curl_hash_clean_with_criterium", scope: !1, file: !1, line: 241, type: !79, isLocal: false, isDefinition: true, scopeLine: 243, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!79 = !DISubroutineType(types: !80)
!80 = !{null, !26, !9, !81}
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{!59, !9, !9}
!84 = distinct !DISubprogram(name: "Curl_hash_str", scope: !1, file: !1, line: 268, type: !46, isLocal: false, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!85 = distinct !DISubprogram(name: "Curl_str_key_compare", scope: !1, file: !1, line: 282, type: !51, isLocal: false, isDefinition: true, scopeLine: 284, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!86 = distinct !DISubprogram(name: "Curl_hash_start_iterate", scope: !1, file: !1, line: 291, type: !87, isLocal: false, isDefinition: true, scopeLine: 293, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!87 = !DISubroutineType(types: !88)
!88 = !{null, !26, !89}
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash_iterator", file: !12, line: 65, size: 192, align: 64, elements: !91)
!91 = !{!92, !93, !94}
!92 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !90, file: !12, line: 66, baseType: !26, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "slot_index", scope: !90, file: !12, line: 67, baseType: !59, size: 32, align: 32, offset: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "current_element", scope: !90, file: !12, line: 68, baseType: !34, size: 64, align: 64, offset: 128)
!95 = distinct !DISubprogram(name: "Curl_hash_next_element", scope: !1, file: !1, line: 300, type: !96, isLocal: false, isDefinition: true, scopeLine: 301, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!96 = !DISubroutineType(types: !97)
!97 = !{!10, !89}
!98 = distinct !DISubprogram(name: "hash_element_dtor", scope: !1, file: !1, line: 35, type: !7, isLocal: true, isDefinition: true, scopeLine: 36, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!99 = distinct !DISubprogram(name: "mk_hash_element", scope: !1, file: !1, line: 86, type: !100, isLocal: true, isDefinition: true, scopeLine: 87, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!100 = !DISubroutineType(types: !101)
!101 = !{!10, !102, !16, !102}
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!104 = !{i32 2, !"Dwarf Version", i32 4}
!105 = !{i32 2, !"Debug Info Version", i32 3}
!106 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!107 = !DILocalVariable(name: "h", arg: 1, scope: !62, file: !1, line: 57, type: !26)
!108 = !DIExpression()
!109 = !DILocation(line: 57, column: 34, scope: !62)
!110 = !DILocalVariable(name: "slots", arg: 2, scope: !62, file: !1, line: 58, type: !59)
!111 = !DILocation(line: 58, column: 20, scope: !62)
!112 = !DILocalVariable(name: "hfunc", arg: 3, scope: !62, file: !1, line: 59, type: !44)
!113 = !DILocation(line: 59, column: 30, scope: !62)
!114 = !DILocalVariable(name: "comparator", arg: 4, scope: !62, file: !1, line: 60, type: !49)
!115 = !DILocation(line: 60, column: 30, scope: !62)
!116 = !DILocalVariable(name: "dtor", arg: 5, scope: !62, file: !1, line: 61, type: !54)
!117 = !DILocation(line: 61, column: 31, scope: !62)
!118 = !DILocalVariable(name: "i", scope: !62, file: !1, line: 63, type: !59)
!119 = !DILocation(line: 63, column: 7, scope: !62)
!120 = !DILocation(line: 65, column: 7, scope: !121)
!121 = distinct !DILexicalBlock(scope: !62, file: !1, line: 65, column: 6)
!122 = !DILocation(line: 65, column: 13, scope: !121)
!123 = !DILocation(line: 65, column: 17, scope: !124)
!124 = !DILexicalBlockFile(scope: !121, file: !1, discriminator: 1)
!125 = !DILocation(line: 65, column: 23, scope: !124)
!126 = !DILocation(line: 65, column: 27, scope: !127)
!127 = !DILexicalBlockFile(scope: !121, file: !1, discriminator: 2)
!128 = !DILocation(line: 65, column: 38, scope: !127)
!129 = !DILocation(line: 65, column: 41, scope: !130)
!130 = !DILexicalBlockFile(scope: !121, file: !1, discriminator: 3)
!131 = !DILocation(line: 65, column: 6, scope: !130)
!132 = !DILocation(line: 66, column: 5, scope: !133)
!133 = distinct !DILexicalBlock(scope: !121, file: !1, line: 65, column: 47)
!134 = !DILocation(line: 69, column: 18, scope: !62)
!135 = !DILocation(line: 69, column: 3, scope: !62)
!136 = !DILocation(line: 69, column: 6, scope: !62)
!137 = !DILocation(line: 69, column: 16, scope: !62)
!138 = !DILocation(line: 70, column: 18, scope: !62)
!139 = !DILocation(line: 70, column: 3, scope: !62)
!140 = !DILocation(line: 70, column: 6, scope: !62)
!141 = !DILocation(line: 70, column: 16, scope: !62)
!142 = !DILocation(line: 71, column: 13, scope: !62)
!143 = !DILocation(line: 71, column: 3, scope: !62)
!144 = !DILocation(line: 71, column: 6, scope: !62)
!145 = !DILocation(line: 71, column: 11, scope: !62)
!146 = !DILocation(line: 72, column: 3, scope: !62)
!147 = !DILocation(line: 72, column: 6, scope: !62)
!148 = !DILocation(line: 72, column: 11, scope: !62)
!149 = !DILocation(line: 73, column: 14, scope: !62)
!150 = !DILocation(line: 73, column: 3, scope: !62)
!151 = !DILocation(line: 73, column: 6, scope: !62)
!152 = !DILocation(line: 73, column: 12, scope: !62)
!153 = !DILocation(line: 75, column: 14, scope: !62)
!154 = !DILocation(line: 75, column: 3, scope: !62)
!155 = !DILocation(line: 75, column: 6, scope: !62)
!156 = !DILocation(line: 75, column: 12, scope: !62)
!157 = !DILocation(line: 76, column: 6, scope: !158)
!158 = distinct !DILexicalBlock(scope: !62, file: !1, line: 76, column: 6)
!159 = !DILocation(line: 76, column: 9, scope: !158)
!160 = !DILocation(line: 76, column: 6, scope: !62)
!161 = !DILocation(line: 77, column: 11, scope: !162)
!162 = distinct !DILexicalBlock(scope: !163, file: !1, line: 77, column: 5)
!163 = distinct !DILexicalBlock(scope: !158, file: !1, line: 76, column: 16)
!164 = !DILocation(line: 77, column: 9, scope: !162)
!165 = !DILocation(line: 77, column: 16, scope: !166)
!166 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!167 = distinct !DILexicalBlock(scope: !162, file: !1, line: 77, column: 5)
!168 = !DILocation(line: 77, column: 20, scope: !166)
!169 = !DILocation(line: 77, column: 18, scope: !166)
!170 = !DILocation(line: 77, column: 5, scope: !166)
!171 = !DILocation(line: 78, column: 33, scope: !167)
!172 = !DILocation(line: 78, column: 24, scope: !167)
!173 = !DILocation(line: 78, column: 27, scope: !167)
!174 = !DILocation(line: 78, column: 7, scope: !167)
!175 = !DILocation(line: 77, column: 27, scope: !176)
!176 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 2)
!177 = !DILocation(line: 77, column: 5, scope: !176)
!178 = !DILocation(line: 79, column: 5, scope: !163)
!179 = !DILocation(line: 81, column: 3, scope: !62)
!180 = !DILocation(line: 81, column: 6, scope: !62)
!181 = !DILocation(line: 81, column: 12, scope: !62)
!182 = !DILocation(line: 82, column: 3, scope: !62)
!183 = !DILocation(line: 83, column: 1, scope: !62)
!184 = !DILocalVariable(name: "user", arg: 1, scope: !98, file: !1, line: 35, type: !9)
!185 = !DILocation(line: 35, column: 25, scope: !98)
!186 = !DILocalVariable(name: "element", arg: 2, scope: !98, file: !1, line: 35, type: !9)
!187 = !DILocation(line: 35, column: 37, scope: !98)
!188 = !DILocalVariable(name: "h", scope: !98, file: !1, line: 37, type: !26)
!189 = !DILocation(line: 37, column: 21, scope: !98)
!190 = !DILocation(line: 37, column: 46, scope: !98)
!191 = !DILocation(line: 37, column: 25, scope: !98)
!192 = !DILocalVariable(name: "e", scope: !98, file: !1, line: 38, type: !10)
!193 = !DILocation(line: 38, column: 29, scope: !98)
!194 = !DILocation(line: 38, column: 62, scope: !98)
!195 = !DILocation(line: 38, column: 33, scope: !98)
!196 = !DILocation(line: 40, column: 6, scope: !197)
!197 = distinct !DILexicalBlock(scope: !98, file: !1, line: 40, column: 6)
!198 = !DILocation(line: 40, column: 9, scope: !197)
!199 = !DILocation(line: 40, column: 6, scope: !98)
!200 = !DILocation(line: 41, column: 5, scope: !201)
!201 = distinct !DILexicalBlock(scope: !197, file: !1, line: 40, column: 14)
!202 = !DILocation(line: 41, column: 8, scope: !201)
!203 = !DILocation(line: 41, column: 13, scope: !201)
!204 = !DILocation(line: 41, column: 16, scope: !201)
!205 = !DILocation(line: 42, column: 5, scope: !201)
!206 = !DILocation(line: 42, column: 8, scope: !201)
!207 = !DILocation(line: 42, column: 12, scope: !201)
!208 = !DILocation(line: 43, column: 3, scope: !201)
!209 = !DILocation(line: 45, column: 3, scope: !98)
!210 = !DILocation(line: 45, column: 6, scope: !98)
!211 = !DILocation(line: 45, column: 14, scope: !98)
!212 = !DILocation(line: 47, column: 3, scope: !98)
!213 = !DILocation(line: 48, column: 1, scope: !98)
!214 = !DILocalVariable(name: "h", arg: 1, scope: !65, file: !1, line: 110, type: !26)
!215 = !DILocation(line: 110, column: 33, scope: !65)
!216 = !DILocalVariable(name: "key", arg: 2, scope: !65, file: !1, line: 110, type: !9)
!217 = !DILocation(line: 110, column: 42, scope: !65)
!218 = !DILocalVariable(name: "key_len", arg: 3, scope: !65, file: !1, line: 110, type: !16)
!219 = !DILocation(line: 110, column: 54, scope: !65)
!220 = !DILocalVariable(name: "p", arg: 4, scope: !65, file: !1, line: 110, type: !9)
!221 = !DILocation(line: 110, column: 69, scope: !65)
!222 = !DILocalVariable(name: "he", scope: !65, file: !1, line: 112, type: !10)
!223 = !DILocation(line: 112, column: 30, scope: !65)
!224 = !DILocalVariable(name: "le", scope: !65, file: !1, line: 113, type: !34)
!225 = !DILocation(line: 113, column: 30, scope: !65)
!226 = !DILocalVariable(name: "l", scope: !65, file: !1, line: 114, type: !30)
!227 = !DILocation(line: 114, column: 22, scope: !65)
!228 = !DILocation(line: 114, column: 26, scope: !65)
!229 = !DILocation(line: 116, column: 12, scope: !230)
!230 = distinct !DILexicalBlock(scope: !65, file: !1, line: 116, column: 3)
!231 = !DILocation(line: 116, column: 15, scope: !230)
!232 = !DILocation(line: 116, column: 10, scope: !230)
!233 = !DILocation(line: 116, column: 7, scope: !230)
!234 = !DILocation(line: 116, column: 21, scope: !235)
!235 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 1)
!236 = distinct !DILexicalBlock(scope: !230, file: !1, line: 116, column: 3)
!237 = !DILocation(line: 116, column: 3, scope: !235)
!238 = !DILocation(line: 117, column: 39, scope: !239)
!239 = distinct !DILexicalBlock(scope: !236, file: !1, line: 116, column: 40)
!240 = !DILocation(line: 117, column: 43, scope: !239)
!241 = !DILocation(line: 117, column: 10, scope: !239)
!242 = !DILocation(line: 117, column: 8, scope: !239)
!243 = !DILocation(line: 118, column: 8, scope: !244)
!244 = distinct !DILexicalBlock(scope: !239, file: !1, line: 118, column: 8)
!245 = !DILocation(line: 118, column: 11, scope: !244)
!246 = !DILocation(line: 118, column: 21, scope: !244)
!247 = !DILocation(line: 118, column: 25, scope: !244)
!248 = !DILocation(line: 118, column: 30, scope: !244)
!249 = !DILocation(line: 118, column: 34, scope: !244)
!250 = !DILocation(line: 118, column: 43, scope: !244)
!251 = !DILocation(line: 118, column: 48, scope: !244)
!252 = !DILocation(line: 118, column: 8, scope: !239)
!253 = !DILocation(line: 119, column: 25, scope: !254)
!254 = distinct !DILexicalBlock(scope: !244, file: !1, line: 118, column: 58)
!255 = !DILocation(line: 119, column: 28, scope: !254)
!256 = !DILocation(line: 119, column: 40, scope: !254)
!257 = !DILocation(line: 119, column: 32, scope: !254)
!258 = !DILocation(line: 119, column: 7, scope: !254)
!259 = !DILocation(line: 120, column: 9, scope: !254)
!260 = !DILocation(line: 120, column: 12, scope: !254)
!261 = !DILocation(line: 120, column: 7, scope: !254)
!262 = !DILocation(line: 121, column: 7, scope: !254)
!263 = !DILocation(line: 123, column: 3, scope: !239)
!264 = !DILocation(line: 116, column: 30, scope: !265)
!265 = !DILexicalBlockFile(scope: !236, file: !1, discriminator: 2)
!266 = !DILocation(line: 116, column: 34, scope: !265)
!267 = !DILocation(line: 116, column: 28, scope: !265)
!268 = !DILocation(line: 116, column: 3, scope: !265)
!269 = !DILocation(line: 125, column: 24, scope: !65)
!270 = !DILocation(line: 125, column: 29, scope: !65)
!271 = !DILocation(line: 125, column: 38, scope: !65)
!272 = !DILocation(line: 125, column: 8, scope: !65)
!273 = !DILocation(line: 125, column: 6, scope: !65)
!274 = !DILocation(line: 126, column: 6, scope: !275)
!275 = distinct !DILexicalBlock(scope: !65, file: !1, line: 126, column: 6)
!276 = !DILocation(line: 126, column: 6, scope: !65)
!277 = !DILocation(line: 127, column: 31, scope: !278)
!278 = distinct !DILexicalBlock(scope: !279, file: !1, line: 127, column: 8)
!279 = distinct !DILexicalBlock(scope: !275, file: !1, line: 126, column: 10)
!280 = !DILocation(line: 127, column: 34, scope: !278)
!281 = !DILocation(line: 127, column: 37, scope: !278)
!282 = !DILocation(line: 127, column: 43, scope: !278)
!283 = !DILocation(line: 127, column: 8, scope: !278)
!284 = !DILocation(line: 127, column: 8, scope: !279)
!285 = !DILocation(line: 128, column: 9, scope: !286)
!286 = distinct !DILexicalBlock(scope: !278, file: !1, line: 127, column: 48)
!287 = !DILocation(line: 128, column: 12, scope: !286)
!288 = !DILocation(line: 128, column: 7, scope: !286)
!289 = !DILocation(line: 129, column: 14, scope: !286)
!290 = !DILocation(line: 129, column: 7, scope: !286)
!291 = !DILocation(line: 137, column: 5, scope: !279)
!292 = !DILocation(line: 138, column: 3, scope: !279)
!293 = !DILocation(line: 140, column: 3, scope: !65)
!294 = !DILocation(line: 141, column: 1, scope: !65)
!295 = !DILocalVariable(name: "key", arg: 1, scope: !99, file: !1, line: 86, type: !102)
!296 = !DILocation(line: 86, column: 29, scope: !99)
!297 = !DILocalVariable(name: "key_len", arg: 2, scope: !99, file: !1, line: 86, type: !16)
!298 = !DILocation(line: 86, column: 41, scope: !99)
!299 = !DILocalVariable(name: "p", arg: 3, scope: !99, file: !1, line: 86, type: !102)
!300 = !DILocation(line: 86, column: 62, scope: !99)
!301 = !DILocalVariable(name: "he", scope: !99, file: !1, line: 89, type: !10)
!302 = !DILocation(line: 89, column: 29, scope: !99)
!303 = !DILocation(line: 89, column: 34, scope: !99)
!304 = !DILocation(line: 91, column: 6, scope: !305)
!305 = distinct !DILexicalBlock(scope: !99, file: !1, line: 91, column: 6)
!306 = !DILocation(line: 91, column: 6, scope: !99)
!307 = !DILocation(line: 93, column: 12, scope: !308)
!308 = distinct !DILexicalBlock(scope: !305, file: !1, line: 91, column: 10)
!309 = !DILocation(line: 93, column: 16, scope: !308)
!310 = !DILocation(line: 93, column: 5, scope: !308)
!311 = !DILocation(line: 93, column: 21, scope: !308)
!312 = !DILocation(line: 93, column: 26, scope: !308)
!313 = !DILocation(line: 94, column: 19, scope: !308)
!314 = !DILocation(line: 94, column: 5, scope: !308)
!315 = !DILocation(line: 94, column: 9, scope: !308)
!316 = !DILocation(line: 94, column: 17, scope: !308)
!317 = !DILocation(line: 95, column: 24, scope: !308)
!318 = !DILocation(line: 95, column: 5, scope: !308)
!319 = !DILocation(line: 95, column: 9, scope: !308)
!320 = !DILocation(line: 95, column: 13, scope: !308)
!321 = !DILocation(line: 96, column: 3, scope: !308)
!322 = !DILocation(line: 97, column: 10, scope: !99)
!323 = !DILocation(line: 97, column: 3, scope: !99)
!324 = !DILocalVariable(name: "h", arg: 1, scope: !68, file: !1, line: 148, type: !26)
!325 = !DILocation(line: 148, column: 40, scope: !68)
!326 = !DILocalVariable(name: "key", arg: 2, scope: !68, file: !1, line: 148, type: !9)
!327 = !DILocation(line: 148, column: 49, scope: !68)
!328 = !DILocalVariable(name: "key_len", arg: 3, scope: !68, file: !1, line: 148, type: !16)
!329 = !DILocation(line: 148, column: 61, scope: !68)
!330 = !DILocalVariable(name: "le", scope: !68, file: !1, line: 150, type: !34)
!331 = !DILocation(line: 150, column: 30, scope: !68)
!332 = !DILocalVariable(name: "he", scope: !68, file: !1, line: 151, type: !10)
!333 = !DILocation(line: 151, column: 30, scope: !68)
!334 = !DILocalVariable(name: "l", scope: !68, file: !1, line: 152, type: !30)
!335 = !DILocation(line: 152, column: 22, scope: !68)
!336 = !DILocation(line: 152, column: 26, scope: !68)
!337 = !DILocation(line: 154, column: 12, scope: !338)
!338 = distinct !DILexicalBlock(scope: !68, file: !1, line: 154, column: 3)
!339 = !DILocation(line: 154, column: 15, scope: !338)
!340 = !DILocation(line: 154, column: 10, scope: !338)
!341 = !DILocation(line: 154, column: 7, scope: !338)
!342 = !DILocation(line: 154, column: 21, scope: !343)
!343 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 1)
!344 = distinct !DILexicalBlock(scope: !338, file: !1, line: 154, column: 3)
!345 = !DILocation(line: 154, column: 3, scope: !343)
!346 = !DILocation(line: 155, column: 10, scope: !347)
!347 = distinct !DILexicalBlock(scope: !344, file: !1, line: 154, column: 40)
!348 = !DILocation(line: 155, column: 14, scope: !347)
!349 = !DILocation(line: 155, column: 8, scope: !347)
!350 = !DILocation(line: 156, column: 8, scope: !351)
!351 = distinct !DILexicalBlock(scope: !347, file: !1, line: 156, column: 8)
!352 = !DILocation(line: 156, column: 11, scope: !351)
!353 = !DILocation(line: 156, column: 21, scope: !351)
!354 = !DILocation(line: 156, column: 25, scope: !351)
!355 = !DILocation(line: 156, column: 30, scope: !351)
!356 = !DILocation(line: 156, column: 34, scope: !351)
!357 = !DILocation(line: 156, column: 43, scope: !351)
!358 = !DILocation(line: 156, column: 48, scope: !351)
!359 = !DILocation(line: 156, column: 8, scope: !347)
!360 = !DILocation(line: 157, column: 25, scope: !361)
!361 = distinct !DILexicalBlock(scope: !351, file: !1, line: 156, column: 58)
!362 = !DILocation(line: 157, column: 28, scope: !361)
!363 = !DILocation(line: 157, column: 41, scope: !361)
!364 = !DILocation(line: 157, column: 32, scope: !361)
!365 = !DILocation(line: 157, column: 7, scope: !361)
!366 = !DILocation(line: 158, column: 9, scope: !361)
!367 = !DILocation(line: 158, column: 12, scope: !361)
!368 = !DILocation(line: 158, column: 7, scope: !361)
!369 = !DILocation(line: 159, column: 7, scope: !361)
!370 = !DILocation(line: 161, column: 3, scope: !347)
!371 = !DILocation(line: 154, column: 30, scope: !372)
!372 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 2)
!373 = !DILocation(line: 154, column: 34, scope: !372)
!374 = !DILocation(line: 154, column: 28, scope: !372)
!375 = !DILocation(line: 154, column: 3, scope: !372)
!376 = !DILocation(line: 162, column: 3, scope: !68)
!377 = !DILocation(line: 163, column: 1, scope: !68)
!378 = !DILocalVariable(name: "h", arg: 1, scope: !71, file: !1, line: 170, type: !26)
!379 = !DILocation(line: 170, column: 34, scope: !71)
!380 = !DILocalVariable(name: "key", arg: 2, scope: !71, file: !1, line: 170, type: !9)
!381 = !DILocation(line: 170, column: 43, scope: !71)
!382 = !DILocalVariable(name: "key_len", arg: 3, scope: !71, file: !1, line: 170, type: !16)
!383 = !DILocation(line: 170, column: 55, scope: !71)
!384 = !DILocalVariable(name: "le", scope: !71, file: !1, line: 172, type: !34)
!385 = !DILocation(line: 172, column: 30, scope: !71)
!386 = !DILocalVariable(name: "he", scope: !71, file: !1, line: 173, type: !10)
!387 = !DILocation(line: 173, column: 30, scope: !71)
!388 = !DILocalVariable(name: "l", scope: !71, file: !1, line: 174, type: !30)
!389 = !DILocation(line: 174, column: 22, scope: !71)
!390 = !DILocation(line: 176, column: 6, scope: !391)
!391 = distinct !DILexicalBlock(scope: !71, file: !1, line: 176, column: 6)
!392 = !DILocation(line: 176, column: 6, scope: !71)
!393 = !DILocation(line: 177, column: 9, scope: !394)
!394 = distinct !DILexicalBlock(scope: !391, file: !1, line: 176, column: 9)
!395 = !DILocation(line: 177, column: 7, scope: !394)
!396 = !DILocation(line: 178, column: 14, scope: !397)
!397 = distinct !DILexicalBlock(scope: !394, file: !1, line: 178, column: 5)
!398 = !DILocation(line: 178, column: 17, scope: !397)
!399 = !DILocation(line: 178, column: 12, scope: !397)
!400 = !DILocation(line: 178, column: 9, scope: !397)
!401 = !DILocation(line: 178, column: 23, scope: !402)
!402 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 1)
!403 = distinct !DILexicalBlock(scope: !397, file: !1, line: 178, column: 5)
!404 = !DILocation(line: 178, column: 5, scope: !402)
!405 = !DILocation(line: 179, column: 12, scope: !406)
!406 = distinct !DILexicalBlock(scope: !403, file: !1, line: 178, column: 42)
!407 = !DILocation(line: 179, column: 16, scope: !406)
!408 = !DILocation(line: 179, column: 10, scope: !406)
!409 = !DILocation(line: 180, column: 10, scope: !410)
!410 = distinct !DILexicalBlock(scope: !406, file: !1, line: 180, column: 10)
!411 = !DILocation(line: 180, column: 13, scope: !410)
!412 = !DILocation(line: 180, column: 23, scope: !410)
!413 = !DILocation(line: 180, column: 27, scope: !410)
!414 = !DILocation(line: 180, column: 32, scope: !410)
!415 = !DILocation(line: 180, column: 36, scope: !410)
!416 = !DILocation(line: 180, column: 45, scope: !410)
!417 = !DILocation(line: 180, column: 50, scope: !410)
!418 = !DILocation(line: 180, column: 10, scope: !406)
!419 = !DILocation(line: 181, column: 16, scope: !420)
!420 = distinct !DILexicalBlock(scope: !410, file: !1, line: 180, column: 60)
!421 = !DILocation(line: 181, column: 20, scope: !420)
!422 = !DILocation(line: 181, column: 9, scope: !420)
!423 = !DILocation(line: 183, column: 5, scope: !406)
!424 = !DILocation(line: 178, column: 32, scope: !425)
!425 = !DILexicalBlockFile(scope: !403, file: !1, discriminator: 2)
!426 = !DILocation(line: 178, column: 36, scope: !425)
!427 = !DILocation(line: 178, column: 30, scope: !425)
!428 = !DILocation(line: 178, column: 5, scope: !425)
!429 = !DILocation(line: 184, column: 3, scope: !394)
!430 = !DILocation(line: 186, column: 3, scope: !71)
!431 = !DILocation(line: 187, column: 1, scope: !71)
!432 = !DILocalVariable(name: "h", arg: 1, scope: !74, file: !1, line: 216, type: !26)
!433 = !DILocation(line: 216, column: 37, scope: !74)
!434 = !DILocalVariable(name: "i", scope: !74, file: !1, line: 218, type: !59)
!435 = !DILocation(line: 218, column: 7, scope: !74)
!436 = !DILocation(line: 220, column: 9, scope: !437)
!437 = distinct !DILexicalBlock(scope: !74, file: !1, line: 220, column: 3)
!438 = !DILocation(line: 220, column: 7, scope: !437)
!439 = !DILocation(line: 220, column: 14, scope: !440)
!440 = !DILexicalBlockFile(scope: !441, file: !1, discriminator: 1)
!441 = distinct !DILexicalBlock(scope: !437, file: !1, line: 220, column: 3)
!442 = !DILocation(line: 220, column: 18, scope: !440)
!443 = !DILocation(line: 220, column: 21, scope: !440)
!444 = !DILocation(line: 220, column: 16, scope: !440)
!445 = !DILocation(line: 220, column: 3, scope: !440)
!446 = !DILocation(line: 221, column: 34, scope: !447)
!447 = distinct !DILexicalBlock(scope: !441, file: !1, line: 220, column: 33)
!448 = !DILocation(line: 221, column: 25, scope: !447)
!449 = !DILocation(line: 221, column: 28, scope: !447)
!450 = !DILocation(line: 221, column: 47, scope: !447)
!451 = !DILocation(line: 221, column: 38, scope: !447)
!452 = !DILocation(line: 221, column: 5, scope: !447)
!453 = !DILocation(line: 222, column: 3, scope: !447)
!454 = !DILocation(line: 220, column: 28, scope: !455)
!455 = !DILexicalBlockFile(scope: !441, file: !1, discriminator: 2)
!456 = !DILocation(line: 220, column: 3, scope: !455)
!457 = !DILocation(line: 224, column: 3, scope: !74)
!458 = !DILocation(line: 224, column: 3, scope: !459)
!459 = !DILexicalBlockFile(scope: !460, file: !1, discriminator: 1)
!460 = distinct !DILexicalBlock(scope: !74, file: !1, line: 224, column: 3)
!461 = !DILocation(line: 225, column: 3, scope: !74)
!462 = !DILocation(line: 225, column: 6, scope: !74)
!463 = !DILocation(line: 225, column: 11, scope: !74)
!464 = !DILocation(line: 226, column: 3, scope: !74)
!465 = !DILocation(line: 226, column: 6, scope: !74)
!466 = !DILocation(line: 226, column: 12, scope: !74)
!467 = !DILocation(line: 227, column: 1, scope: !74)
!468 = !DILocalVariable(name: "h", arg: 1, scope: !77, file: !1, line: 234, type: !26)
!469 = !DILocation(line: 234, column: 35, scope: !77)
!470 = !DILocation(line: 236, column: 34, scope: !77)
!471 = !DILocation(line: 236, column: 3, scope: !77)
!472 = !DILocation(line: 237, column: 1, scope: !77)
!473 = !DILocalVariable(name: "h", arg: 1, scope: !78, file: !1, line: 241, type: !26)
!474 = !DILocation(line: 241, column: 50, scope: !78)
!475 = !DILocalVariable(name: "user", arg: 2, scope: !78, file: !1, line: 241, type: !9)
!476 = !DILocation(line: 241, column: 59, scope: !78)
!477 = !DILocalVariable(name: "comp", arg: 3, scope: !78, file: !1, line: 242, type: !81)
!478 = !DILocation(line: 242, column: 38, scope: !78)
!479 = !DILocalVariable(name: "le", scope: !78, file: !1, line: 244, type: !34)
!480 = !DILocation(line: 244, column: 30, scope: !78)
!481 = !DILocalVariable(name: "lnext", scope: !78, file: !1, line: 245, type: !34)
!482 = !DILocation(line: 245, column: 30, scope: !78)
!483 = !DILocalVariable(name: "list", scope: !78, file: !1, line: 246, type: !30)
!484 = !DILocation(line: 246, column: 22, scope: !78)
!485 = !DILocalVariable(name: "i", scope: !78, file: !1, line: 247, type: !59)
!486 = !DILocation(line: 247, column: 7, scope: !78)
!487 = !DILocation(line: 249, column: 7, scope: !488)
!488 = distinct !DILexicalBlock(scope: !78, file: !1, line: 249, column: 6)
!489 = !DILocation(line: 249, column: 6, scope: !78)
!490 = !DILocation(line: 250, column: 5, scope: !488)
!491 = !DILocation(line: 252, column: 9, scope: !492)
!492 = distinct !DILexicalBlock(scope: !78, file: !1, line: 252, column: 3)
!493 = !DILocation(line: 252, column: 7, scope: !492)
!494 = !DILocation(line: 252, column: 14, scope: !495)
!495 = !DILexicalBlockFile(scope: !496, file: !1, discriminator: 1)
!496 = distinct !DILexicalBlock(scope: !492, file: !1, line: 252, column: 3)
!497 = !DILocation(line: 252, column: 18, scope: !495)
!498 = !DILocation(line: 252, column: 21, scope: !495)
!499 = !DILocation(line: 252, column: 16, scope: !495)
!500 = !DILocation(line: 252, column: 3, scope: !495)
!501 = !DILocation(line: 253, column: 22, scope: !502)
!502 = distinct !DILexicalBlock(scope: !496, file: !1, line: 252, column: 33)
!503 = !DILocation(line: 253, column: 13, scope: !502)
!504 = !DILocation(line: 253, column: 16, scope: !502)
!505 = !DILocation(line: 253, column: 10, scope: !502)
!506 = !DILocation(line: 254, column: 10, scope: !502)
!507 = !DILocation(line: 254, column: 16, scope: !502)
!508 = !DILocation(line: 254, column: 8, scope: !502)
!509 = !DILocation(line: 255, column: 5, scope: !502)
!510 = !DILocation(line: 255, column: 11, scope: !511)
!511 = !DILexicalBlockFile(scope: !502, file: !1, discriminator: 1)
!512 = !DILocation(line: 255, column: 5, scope: !511)
!513 = !DILocalVariable(name: "he", scope: !514, file: !1, line: 256, type: !10)
!514 = distinct !DILexicalBlock(scope: !502, file: !1, line: 255, column: 15)
!515 = !DILocation(line: 256, column: 33, scope: !514)
!516 = !DILocation(line: 256, column: 38, scope: !514)
!517 = !DILocation(line: 256, column: 42, scope: !514)
!518 = !DILocation(line: 257, column: 15, scope: !514)
!519 = !DILocation(line: 257, column: 19, scope: !514)
!520 = !DILocation(line: 257, column: 13, scope: !514)
!521 = !DILocation(line: 259, column: 10, scope: !522)
!522 = distinct !DILexicalBlock(scope: !514, file: !1, line: 259, column: 10)
!523 = !DILocation(line: 259, column: 15, scope: !522)
!524 = !DILocation(line: 259, column: 23, scope: !522)
!525 = !DILocation(line: 259, column: 26, scope: !526)
!526 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 1)
!527 = !DILocation(line: 259, column: 31, scope: !526)
!528 = !DILocation(line: 259, column: 37, scope: !526)
!529 = !DILocation(line: 259, column: 41, scope: !526)
!530 = !DILocation(line: 259, column: 10, scope: !526)
!531 = !DILocation(line: 260, column: 27, scope: !532)
!532 = distinct !DILexicalBlock(scope: !522, file: !1, line: 259, column: 47)
!533 = !DILocation(line: 260, column: 33, scope: !532)
!534 = !DILocation(line: 260, column: 46, scope: !532)
!535 = !DILocation(line: 260, column: 37, scope: !532)
!536 = !DILocation(line: 260, column: 9, scope: !532)
!537 = !DILocation(line: 261, column: 11, scope: !532)
!538 = !DILocation(line: 261, column: 14, scope: !532)
!539 = !DILocation(line: 261, column: 9, scope: !532)
!540 = !DILocation(line: 262, column: 7, scope: !532)
!541 = !DILocation(line: 263, column: 12, scope: !514)
!542 = !DILocation(line: 263, column: 10, scope: !514)
!543 = !DILocation(line: 255, column: 5, scope: !544)
!544 = !DILexicalBlockFile(scope: !502, file: !1, discriminator: 2)
!545 = !DILocation(line: 265, column: 3, scope: !502)
!546 = !DILocation(line: 252, column: 28, scope: !547)
!547 = !DILexicalBlockFile(scope: !496, file: !1, discriminator: 2)
!548 = !DILocation(line: 252, column: 3, scope: !547)
!549 = !DILocation(line: 266, column: 1, scope: !78)
!550 = !DILocalVariable(name: "key", arg: 1, scope: !84, file: !1, line: 268, type: !9)
!551 = !DILocation(line: 268, column: 28, scope: !84)
!552 = !DILocalVariable(name: "key_length", arg: 2, scope: !84, file: !1, line: 268, type: !16)
!553 = !DILocation(line: 268, column: 40, scope: !84)
!554 = !DILocalVariable(name: "slots_num", arg: 3, scope: !84, file: !1, line: 268, type: !16)
!555 = !DILocation(line: 268, column: 59, scope: !84)
!556 = !DILocalVariable(name: "key_str", scope: !84, file: !1, line: 270, type: !24)
!557 = !DILocation(line: 270, column: 15, scope: !84)
!558 = !DILocation(line: 270, column: 40, scope: !84)
!559 = !DILocalVariable(name: "end", scope: !84, file: !1, line: 271, type: !24)
!560 = !DILocation(line: 271, column: 15, scope: !84)
!561 = !DILocation(line: 271, column: 21, scope: !84)
!562 = !DILocation(line: 271, column: 31, scope: !84)
!563 = !DILocation(line: 271, column: 29, scope: !84)
!564 = !DILocalVariable(name: "h", scope: !84, file: !1, line: 272, type: !18)
!565 = !DILocation(line: 272, column: 17, scope: !84)
!566 = !DILocation(line: 274, column: 3, scope: !84)
!567 = !DILocation(line: 274, column: 9, scope: !568)
!568 = !DILexicalBlockFile(scope: !84, file: !1, discriminator: 1)
!569 = !DILocation(line: 274, column: 19, scope: !568)
!570 = !DILocation(line: 274, column: 17, scope: !568)
!571 = !DILocation(line: 274, column: 3, scope: !568)
!572 = !DILocation(line: 275, column: 10, scope: !573)
!573 = distinct !DILexicalBlock(scope: !84, file: !1, line: 274, column: 24)
!574 = !DILocation(line: 275, column: 12, scope: !573)
!575 = !DILocation(line: 275, column: 7, scope: !573)
!576 = !DILocation(line: 276, column: 34, scope: !573)
!577 = !DILocation(line: 276, column: 26, scope: !573)
!578 = !DILocation(line: 276, column: 10, scope: !573)
!579 = !DILocation(line: 276, column: 7, scope: !573)
!580 = !DILocation(line: 274, column: 3, scope: !581)
!581 = !DILexicalBlockFile(scope: !84, file: !1, discriminator: 2)
!582 = !DILocation(line: 279, column: 11, scope: !84)
!583 = !DILocation(line: 279, column: 15, scope: !84)
!584 = !DILocation(line: 279, column: 13, scope: !84)
!585 = !DILocation(line: 279, column: 3, scope: !84)
!586 = !DILocalVariable(name: "k1", arg: 1, scope: !85, file: !1, line: 282, type: !9)
!587 = !DILocation(line: 282, column: 35, scope: !85)
!588 = !DILocalVariable(name: "key1_len", arg: 2, scope: !85, file: !1, line: 282, type: !16)
!589 = !DILocation(line: 282, column: 46, scope: !85)
!590 = !DILocalVariable(name: "k2", arg: 3, scope: !85, file: !1, line: 283, type: !9)
!591 = !DILocation(line: 283, column: 35, scope: !85)
!592 = !DILocalVariable(name: "key2_len", arg: 4, scope: !85, file: !1, line: 283, type: !16)
!593 = !DILocation(line: 283, column: 46, scope: !85)
!594 = !DILocation(line: 285, column: 7, scope: !595)
!595 = distinct !DILexicalBlock(scope: !85, file: !1, line: 285, column: 6)
!596 = !DILocation(line: 285, column: 19, scope: !595)
!597 = !DILocation(line: 285, column: 16, scope: !595)
!598 = !DILocation(line: 285, column: 29, scope: !595)
!599 = !DILocation(line: 285, column: 40, scope: !600)
!600 = !DILexicalBlockFile(scope: !595, file: !1, discriminator: 1)
!601 = !DILocation(line: 285, column: 44, scope: !600)
!602 = !DILocation(line: 285, column: 48, scope: !600)
!603 = !DILocation(line: 285, column: 33, scope: !600)
!604 = !DILocation(line: 285, column: 6, scope: !600)
!605 = !DILocation(line: 286, column: 5, scope: !595)
!606 = !DILocation(line: 288, column: 3, scope: !85)
!607 = !DILocation(line: 289, column: 1, scope: !85)
!608 = !DILocalVariable(name: "hash", arg: 1, scope: !86, file: !1, line: 291, type: !26)
!609 = !DILocation(line: 291, column: 48, scope: !86)
!610 = !DILocalVariable(name: "iter", arg: 2, scope: !86, file: !1, line: 292, type: !89)
!611 = !DILocation(line: 292, column: 57, scope: !86)
!612 = !DILocation(line: 294, column: 16, scope: !86)
!613 = !DILocation(line: 294, column: 3, scope: !86)
!614 = !DILocation(line: 294, column: 9, scope: !86)
!615 = !DILocation(line: 294, column: 14, scope: !86)
!616 = !DILocation(line: 295, column: 3, scope: !86)
!617 = !DILocation(line: 295, column: 9, scope: !86)
!618 = !DILocation(line: 295, column: 20, scope: !86)
!619 = !DILocation(line: 296, column: 3, scope: !86)
!620 = !DILocation(line: 296, column: 9, scope: !86)
!621 = !DILocation(line: 296, column: 25, scope: !86)
!622 = !DILocation(line: 297, column: 1, scope: !86)
!623 = !DILocalVariable(name: "iter", arg: 1, scope: !95, file: !1, line: 300, type: !89)
!624 = !DILocation(line: 300, column: 51, scope: !95)
!625 = !DILocalVariable(name: "i", scope: !95, file: !1, line: 302, type: !59)
!626 = !DILocation(line: 302, column: 7, scope: !95)
!627 = !DILocalVariable(name: "h", scope: !95, file: !1, line: 303, type: !26)
!628 = !DILocation(line: 303, column: 21, scope: !95)
!629 = !DILocation(line: 303, column: 25, scope: !95)
!630 = !DILocation(line: 303, column: 31, scope: !95)
!631 = !DILocation(line: 306, column: 6, scope: !632)
!632 = distinct !DILexicalBlock(scope: !95, file: !1, line: 306, column: 6)
!633 = !DILocation(line: 306, column: 12, scope: !632)
!634 = !DILocation(line: 306, column: 6, scope: !95)
!635 = !DILocation(line: 307, column: 29, scope: !632)
!636 = !DILocation(line: 307, column: 35, scope: !632)
!637 = !DILocation(line: 307, column: 52, scope: !632)
!638 = !DILocation(line: 307, column: 5, scope: !632)
!639 = !DILocation(line: 307, column: 11, scope: !632)
!640 = !DILocation(line: 307, column: 27, scope: !632)
!641 = !DILocation(line: 310, column: 7, scope: !642)
!642 = distinct !DILexicalBlock(scope: !95, file: !1, line: 310, column: 6)
!643 = !DILocation(line: 310, column: 13, scope: !642)
!644 = !DILocation(line: 310, column: 6, scope: !95)
!645 = !DILocation(line: 311, column: 13, scope: !646)
!646 = distinct !DILexicalBlock(scope: !647, file: !1, line: 311, column: 5)
!647 = distinct !DILexicalBlock(scope: !642, file: !1, line: 310, column: 30)
!648 = !DILocation(line: 311, column: 19, scope: !646)
!649 = !DILocation(line: 311, column: 11, scope: !646)
!650 = !DILocation(line: 311, column: 9, scope: !646)
!651 = !DILocation(line: 311, column: 30, scope: !652)
!652 = !DILexicalBlockFile(scope: !653, file: !1, discriminator: 1)
!653 = distinct !DILexicalBlock(scope: !646, file: !1, line: 311, column: 5)
!654 = !DILocation(line: 311, column: 34, scope: !652)
!655 = !DILocation(line: 311, column: 37, scope: !652)
!656 = !DILocation(line: 311, column: 32, scope: !652)
!657 = !DILocation(line: 311, column: 5, scope: !652)
!658 = !DILocation(line: 312, column: 19, scope: !659)
!659 = distinct !DILexicalBlock(scope: !660, file: !1, line: 312, column: 10)
!660 = distinct !DILexicalBlock(scope: !653, file: !1, line: 311, column: 48)
!661 = !DILocation(line: 312, column: 10, scope: !659)
!662 = !DILocation(line: 312, column: 13, scope: !659)
!663 = !DILocation(line: 312, column: 22, scope: !659)
!664 = !DILocation(line: 312, column: 10, scope: !660)
!665 = !DILocation(line: 313, column: 42, scope: !666)
!666 = distinct !DILexicalBlock(scope: !659, file: !1, line: 312, column: 28)
!667 = !DILocation(line: 313, column: 33, scope: !666)
!668 = !DILocation(line: 313, column: 36, scope: !666)
!669 = !DILocation(line: 313, column: 45, scope: !666)
!670 = !DILocation(line: 313, column: 9, scope: !666)
!671 = !DILocation(line: 313, column: 15, scope: !666)
!672 = !DILocation(line: 313, column: 31, scope: !666)
!673 = !DILocation(line: 314, column: 28, scope: !666)
!674 = !DILocation(line: 314, column: 29, scope: !666)
!675 = !DILocation(line: 314, column: 9, scope: !666)
!676 = !DILocation(line: 314, column: 15, scope: !666)
!677 = !DILocation(line: 314, column: 26, scope: !666)
!678 = !DILocation(line: 315, column: 9, scope: !666)
!679 = !DILocation(line: 317, column: 5, scope: !660)
!680 = !DILocation(line: 311, column: 44, scope: !681)
!681 = !DILexicalBlockFile(scope: !653, file: !1, discriminator: 2)
!682 = !DILocation(line: 311, column: 5, scope: !681)
!683 = !DILocation(line: 318, column: 3, scope: !647)
!684 = !DILocation(line: 320, column: 6, scope: !685)
!685 = distinct !DILexicalBlock(scope: !95, file: !1, line: 320, column: 6)
!686 = !DILocation(line: 320, column: 12, scope: !685)
!687 = !DILocation(line: 320, column: 6, scope: !95)
!688 = !DILocalVariable(name: "he", scope: !689, file: !1, line: 321, type: !10)
!689 = distinct !DILexicalBlock(scope: !685, file: !1, line: 320, column: 29)
!690 = !DILocation(line: 321, column: 31, scope: !689)
!691 = !DILocation(line: 321, column: 36, scope: !689)
!692 = !DILocation(line: 321, column: 42, scope: !689)
!693 = !DILocation(line: 321, column: 59, scope: !689)
!694 = !DILocation(line: 322, column: 12, scope: !689)
!695 = !DILocation(line: 322, column: 5, scope: !689)
!696 = !DILocation(line: 324, column: 3, scope: !95)
!697 = !DILocation(line: 324, column: 9, scope: !95)
!698 = !DILocation(line: 324, column: 25, scope: !95)
!699 = !DILocation(line: 325, column: 3, scope: !95)
!700 = !DILocation(line: 326, column: 1, scope: !95)
